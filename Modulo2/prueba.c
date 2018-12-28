#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <ftw.h> 

int main(){
    char cadena[50];

    read(STDIN_FILENO, cadena, 50);

    printf("Cadena %s", cadena);
}