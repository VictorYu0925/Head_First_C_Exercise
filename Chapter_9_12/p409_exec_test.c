#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
    if (execl("sbin/ifconfig", "sbin/ifconfig", NULL) == -1)
        if (execlp("ifconfig", "ifconfig", NULL) == -1) {
            fprintf(stderr, "Cannot run ipconfig: %s", strerror(errno));
            return 1;
        }
    return 0;
}