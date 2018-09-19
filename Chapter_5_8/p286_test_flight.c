#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct island
{
  // 遞迴結構中不允許使用typedef別名，因此必須賦予名稱。
  char *name;
  char *opens;
  char *closes;
  struct island *next;
  // 在struct 中儲存指向下一個島嶼的指標。
} island;

void display(island *start)
{
  island *i = start;
  for (; i != NULL; i = i->next)
  {
    // 迴圈開始時不需要特別的程式碼，每次結尾時就跳到下一個島嶼，直到當前島嶼next為NULL
    printf("Name: %s open: %s-%s\n", i->name, i->opens, i->closes);
  }
}

island* create(char *name) 
// 建立回傳island*型別之函式
{
  island *i = malloc(sizeof(island));
  i->name = strdup(name);
  i->opens = "09:00";
  i->closes = "17:00";
  i->next = NULL;
  return i;
}

void release(island *start)
{
  island *i = start;
  island *next = NULL;
  for(; i != NULL; i = next) {
  next = i->next;
  free(i->name);
  free(i);
  }
}

void main()
{
  island *start = NULL;
  island *i = NULL;
  island *next = NULL;
  char name[80];
  for(;fgets(name, 80, stdin) != NULL; i = next) {
    next = create(name);
    if(start == NULL)
      start = next;
    if(i != NULL)
      i->next = next;
  }
  display(start);
  release(start);
}

