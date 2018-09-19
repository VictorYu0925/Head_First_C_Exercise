#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void error(char *msg)
{
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

int main(int argc, char *argv[])
{
  char *phrase = argv[1];
  char *vars[] = {"RSS_FEED=http://rss.cnn.com/rss/money_lifestyle.xml",
                  NULL};
  FILE *f = fopen("stories.txt", "w");
  if(!f) {
    error("Can't open stories.txt");
  }
  pid_t pid = fork();
  if (pid == -1) {
    error("Cna't fork process");
  }
  if (!pid) {
    if (dup2(fileno(f), 1) == -1) {
      error("Can't redirect Standard Output");
    }
    if (execle("/bin/python", "/bin/python", "./rssgossip.py",
    phrase, NULL, vars) == -1) {
      error("Can't run script");
    }
  }
  return 0;
}


