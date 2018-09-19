#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

int listener_d;
// 存放伺服器的主要偵聽器socket

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  // 展示錯誤
  exit(1);
  // 以狀態1停止程式
}

int open_listener_socket()
{
  int s = socket(PF_INET, SOCK_STREAM, 0);
  // listener_d是該socket的描述子
  // 0為協定數字
  if (s == -1)
    error("Can't open socket");
  return s;
}

void bind_to_port(int socket, int port)
{
  // 建立埠口port的埠口名稱 {
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  // }
  int reuse = 1;
  // 需要int變數存放選項，設為1表示: 是的，請重新利用這個埠口
  if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    error("Can't set the reuse option on the socket");
  int c = bind(socket, (struct sockaddr *)&name, sizeof(name));
  // 抓取埠口
  if (c == -1)
    error("Can't bind to socket");
}

int say(int socket, char *s)
{
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
    fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
  // 若有問題不要呼叫error()，因為假如只有一個客戶端出問題，不需要終止整個伺服器程式
  return result;
}

int read_in(int socket, char *buf, int len)
// 讀取所有字元，直到它到達\n
{
  char *s = buf;
  int slen = len;
  int c = recv(socket, s, slen, 0);
  /*
  printf("in: [%s]\n", s);
  for (int i = 0; i < c; ++i)
  {
    printf("%d\n", s[i]);
  }
  */

  char* tmp_str = s;
  s += c;
  slen -= c;

  // printf("len: %d, c: %d\n", len, c);
  
  while ((c > 0) && (tmp_str[c - 1] != '\n' && tmp_str[c - 1] != '\r' && tmp_str[c - 1] != '\0'))
  {
    c = recv(socket, s, slen, 0);
    // 繼續讀取，直到沒有字元或達到\n
    tmp_str = s;
    s += c;
    slen -= c;
    // s位移c字元(為上一次讀取量)，slen為buf長度-已讀取。
  }
  if (c < 0)
    return c;
  // 假如有錯誤，回傳c
  else if (c == 0)
    buf[0] = '\0';
  // 假如沒有東西被讀取，送回空字串
  else
    tmp_str[c - 1] = '\0';
  // 以 '\0' 替換 '\r'字元
  // printf("str: %s\n", s);
  // printf("%d %d\n", len, slen);
  return len - slen;
  // 總已讀取量= buf長度- slen = buf長度- (buf長度 -已讀取)
}

void handle_shutdown(int sig)
{
  if (listener_d)
    close(listener_d);

  fprintf(stderr, "Bye!\n");
  exit(0);
}

int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  // 建立新動作(action)
  action.sa_handler = handler;
  // 將action的處理器設定為傳進來的處理器函式
  sigemptyset(&action.sa_mask);
  // mask(遮罩)是過濾sigaction將處理之信號的機制
  // 通常會使用空的mask
  action.sa_flags = 0;
  // 額外旗標
  return sigaction(sig, &action, NULL);
}


int main(int argc, char *argv[])
{
  if(catch_signal(SIGINT, handle_shutdown) == -1)
    error("Can't set the interrupt handler");

  char buf[255];
  char *revp[] = {
      "Internet Knock-Knock Protocol Server\r\nVersion 1.0\r\nKnock-Knock!\r\n",
      "Oscar\r\n",
      "Oscar silly question, you get a silly answer\r\n"};
  char *check[] = {
      "Who's there?",
      "Oscar who?"};

  /* ---Bind--- */
  listener_d = open_listener_socket();
  bind_to_port(listener_d, 30000);

  /* ---Listen--- */
  if (listen(listener_d, 10) == -1)
    error("Can't listen");
  

  /* ---Accept--- */
  struct sockaddr_storage client_addr;
  // client_addr 儲存連接上伺服器之客戶端細節資訊
  unsigned int address_size = sizeof(client_addr);
  puts("Waiting for connection");

  while (1) {
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    // 建立用於實際對話的第二個socket描述子
    if (connect_d == -1)
      error("Can't open secondary socket");

    // 子行程
    if (!fork()) {
      close(listener_d);
      /* ---Begin--- */
      if (send(connect_d, revp[0], strlen(revp[0]), 0) == -1)
        // connect_d為socket描述子，strlen(msg)為訊息長度，最後的參數是進階選項可保持0
        error("send");

      for (int i = 0; i < 2; i++)
      {
        int n = 0;
        n = read_in(connect_d, buf, strlen(check[i]) + 2);

        printf("%d %d\n", n, strlen(check[i]));

        int j = 0;
        for (; j < strlen(buf); ++j)
        {
          printf("[%c] %d\n", buf[j], buf[j]);

          if (buf[j] == '\r')
          {
            buf[j] = '\0';
            break;
          }
        }

        printf("[%s][%s]", check[i], buf);

        if (strncasecmp(check[i], buf, strlen(buf)) == 0)
        {
          say(connect_d, revp[i + 1]);
        }
        else
          raise(SIGINT);
      }
      close(connect_d);
      exit(0);
    }
    close(connect_d);
  }

}
