#include <stdio.h>

typedef struct island {
  // 遞迴結構中不允許使用typedef別名，因此必須賦予名稱。
  char *name;
  char *opens;
  char *closes;
  struct island *next;
  // 在struct 中儲存指向下一個島嶼的指標。
} island;

island amity = {"Amity", "09:00", "17:00", NULL};
island craggy = {"Craggy", "09:00", "17:00", NULL};
island isla_nublar = {"Isla Nublar", "09:00", "17:00", NULL};
island shutter = {"Shutter", "09:00", "17:00", NULL};
island skull = {"Skull", "09:00", "17:00", NULL};


void display(island *start)
{
  amity.next = &craggy;
  craggy.next = &isla_nublar;
  isla_nublar.next = &shutter;
  isla_nublar.next = &skull;
  skull.next = &shutter;
  island *i = start;
  for ( ; i != NULL ; i = i->next) {
  // 迴圈開始時不需要特別的程式碼，每次結尾時就跳到下一個島嶼，直到當前島嶼next為NULL
    printf("Name: %s open: %s-%s\n", i->name, i->opens, i->closes);
  }
}

void main() {
  display(&amity);
}
