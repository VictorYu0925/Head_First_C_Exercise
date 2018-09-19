#include <stdio.h>

void fortune_cookie(char msg[])
{
  printf("Msg occupies %i bytes\n ", sizeof(msg));
}

int main()
{
  char quote[] = "cookies make you fat";
  printf("Msg occupies %i bytes\n ", sizeof(quote));
  fortune_cookie(quote);
  return 0;
}

