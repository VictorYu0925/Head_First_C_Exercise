#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  // 展示錯誤
  exit(1);
  // 以狀態1停止程式
}

int main(int argc, char *argv[])
{
  char *advice[] = {
    "Take smaller bites\r\n",
    "Go for the tight jeans. No they do NOT make you look fat.\r\n",
    "One word: inappropriate\r\n",
    "Just for today, be honest. Tell your boss what you *really* think\r\n",
    "You might want to rethink that haircut\r\n"
  };
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  // listener_d是該socket的描述子
  // 0為協定數字
  if (listener_d == -1)
    error("Can't open socket");

  // 建立埠口3000的埠口名稱 {
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  // }
  int reuse = 1;
  // 需要int變數存放選項，設為1表示: 是的，請重新利用這個埠口
  if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    error("Can't set the reuse option on the socket");
  int c = bind(listener_d, (struct sockaddr *)&name, sizeof(name));
  if (c == -1)
    error("Can't bind to socket");



  // 使用長度為10的佇列
  if (listen(listener_d, 10) == -1)
    error("Can't listen");
  else
  puts ("Waiting for connection");

  while(1) {
    struct sockaddr_storage client_addr;
    // client_addr 儲存連接上伺服器之客戶端細節資訊
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    if (connect_d == -1)
      error("Can't open secondary socket");

    char *msg = advice[rand() % 5];
    // msg為即將跨網路傳送的訊息
    if (send(connect_d, msg, strlen(msg), 0) == -1)
      // connect_d為socket描述子，strlen(msg)為訊息長度，最後的參數是進階選項可保持0
      error("send");
    close(connect_d);
  }
  return 0;
}










