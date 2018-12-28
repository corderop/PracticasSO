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

long int totalTamano = 0,
         totalEjecucion = 0;

int procesar(const char* path, const struct stat* stat, int flags, struct FTW*ftw){
    
    if(!S_ISDIR(stat->st_mode)){
        printf("%s %li\n", path, stat->st_size);
        totalTamano += stat->st_size;

        if(((S_IXOTH & stat->st_mode) != 0) && ((S_IXGRP & stat->st_mode) != 0)){
            totalEjecucion++;
        }
    }

    return 0;
}

int main(int argc, char* argv[]){
    char *pathname;

    if(argc != 2){
        printf("Forma errónea de introducir los datos. Forma correcta: \n\t./programa <pathname>");
        exit(-1);
    }
    else
        pathname = argv[1];

    printf("\nLos inodos son:\n");

    if (nftw(pathname, procesar, 10, 0) != 0) { 
        perror("nftw"); 
    } 

    printf("\nExisten %li archivos regulares con permiso x para grupo y otros",totalEjecucion);
    printf("\nEl Tamano total ocupado por dichos archivos es %ld bytes",totalTamano);
}