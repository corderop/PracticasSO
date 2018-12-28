// Cordero Romero, Pablo
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

int procesar(const char* path, const struct stat* stat1, int flags, struct FTW *ftw){
    DIR *dp;
    struct dirent *estructura;
    char cadena[50];
    struct stat atributos;

    if(flags == FTW_D){
        dp = opendir(path);
        while((estructura = readdir(dp)) != NULL){
            if(strcmp(estructura->d_name,".")!=0 && strcmp(estructura->d_name,"..")!=0){
                sprintf(cadena,"/tmp/%s", estructura->d_name);
                if(open(cadena, O_RDONLY)>=0){
                    sprintf(cadena,"%s/%s", path,estructura->d_name);
                    lstat(cadena, &atributos);
                    printf("%s %ld %o\n",estructura->d_name,atributos.st_size, atributos.st_mode&0777);
                }
            }
        }
    }
    

    return 0;
}

int main(int argc, char* argv[]){
    char pathname[50];

    if(argc!=2){
        perror("Introducción de archivos");
        exit(-1);
    }
    else{
        sprintf(pathname,"%s/%s",getenv("HOME"),argv[1]);

        if (nftw(pathname, procesar, 10, 0) != 0) { 
            perror("nftw"); 
        }
    }

    return 0;
}