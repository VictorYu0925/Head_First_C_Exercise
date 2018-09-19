#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

// 信號處理器，sig為信號
void diediedie(int sig)
{
  puts ("Goodbye cruel world....\n");
  exit(1);
}

// 註冊處理器的函式
int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  // 建立新動作(action)
  action.sa_handler = handler;
  // 希望呼叫的函式(處理器)名稱
  sigemptyset(&action.sa_mask);
  // mask(遮罩)是過濾sigaction將處理之信號的機制
  // 通常會使用空的mask
  action.sa_flags = 0;
  // 額外旗標
  return sigaction (sig, &action, NULL);
}


int main()
{
  // 捕捉SIGINT中斷信號，並以diediedie函式作為中斷處理器
  if (catch_signal(SIGINT, diediedie) == -1)
  {
    fprintf(stderr, "Can't map the handlere");
    exit(2);
  }
  char name[30];
  printf("Enter your name: ");
  fgets(name, 30, stdin);
  printf("Hello %s\n", name);
  return 0;
}


