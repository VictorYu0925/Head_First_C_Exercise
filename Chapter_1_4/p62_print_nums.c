#include <stdio.h>

void skip(char* msg)
{
  puts(msg+6);
}

int main(){
  char* msg_from_amy = "k\n";
  puts(msg_from_amy);
  skip(msg_from_amy);
}
