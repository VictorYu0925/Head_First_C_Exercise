#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_scores(const void* score_a, const void*score_b)
{
  int a = * (int*)score_a;
  // 強制轉型後取位址
  int b = * (int*)score_b;
  return a - b;
  // a>b時為正數，交換順序，形成由小到大排序
}

int compare_scores_desc(const void* score_a, const void* score_b)
{
  int a = *(int*)score_a;
  int b = *(int*)score_b;
  return b - a;
}

typedef struct {
  int width;
  int hight;
} rectangle;

int compare_areas(const void *a, const void *b)
{
  rectangle* ra = (rectangle*)a;
  rectangle* rb = (rectangle*)b;
  int area_a = (ra->width * ra->hight);
  int area_b = (ra->width * ra->hight);
  return area_a - area_b;
}

int compare_names(const void *a, const void *b)
{
  char **sa = (char**)a;
  char **sb = (char**)b;
  return strcmp(*sa ,*sb);
}

int compare_areas_desc(const void* a, void* b)
{
  return -(compare_areas(a,b));
}

int compare_names_desc(const void *a, void *b)
{
  return -(compare_names(a, b));
}

int main()
{
  int scores[] = {543, 323, 32, 554, 11, 3, 112};
  int i;
  qsort(scores, 7, sizeof(int), compare_scores_desc);
  puts("These are the score in order:");
  for(i = 0; i < 7 ; i++){
    printf("Score = %i\n", scores[i]);
  }
  char *names[] = {"Karen", "Mark", "Brett", "Molly"};
  qsort(names, 4, sizeof(char*), compare_names);
  puts("Thease are the names in order:");
  for (i = 0; i < 4; i++) {
    printf("%s\n", names[i]);
  }
  return 0;
}