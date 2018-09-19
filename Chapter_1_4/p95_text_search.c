#include <stdio.h>
#include <string.h>

char tracks[][80] = {
  "I left my heart in Harvard Med School",
  "Newark, Newark - a wonderful town",
  "Dancing with a Dork",
  "From here to maternity"
  "The girl from Iwo Jima",
};

void find_track(char search_for[]){
  for(int i = 0; i < 5; i++) {
    if (strstr(tracks[i], search_for))
      printf("Track %i: '%s'\n", i, tracks[i]);
  }  
}

int main(){
  char search_for[80];
  printf("search for: ");
  scanf("%79s", search_for);
  search_for[strlen(search_for) - 1] = '\0';
  find_track(search_for);
  return 0;
}

struct preferences {
  const char *food;
  float exercise_hours;
}

struct fish
{
  const char *name;
  int age;
  struct preferences care;
}

