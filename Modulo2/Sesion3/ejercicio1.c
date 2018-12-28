/**
    Implementa un programa en C que tenga como argumento un número entero. Este programa 
    debe crear un proceso hijo que se encargará de comprobar si dicho número es un número 
    par o impar e informará al usuario con un mensaje que se enviará por la salida estándar.
    A su vez, el proceso padre comprobará si dicho número es divisible por 4, e informará 
    si lo es o no usando igualmente la salida estándar.
*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    int entrada;
    pid_t pid;

    if(argc != 2){
        printf("Forma de introducir datos:\n\n\t./programa <numero_entero>");
        exit(-1);
    }
    else{
        entrada = strtol(argv[1], NULL, 10);
    }

    if((pid = fork())<0){
        printf("Error en el fork");
        exit(-1);
    }
    if(pid == 0){
        // Es el proceso hijo ya que para el mismo el identificador es 0
        printf("\nSoy el proceso hijo y mi pid es %d y el de mi padre %d", getpid(), getppid());
        if(entrada%2 == 0)
            printf("\n\tEl número es par");
        else
            printf("\n\tEl número es impar");
    }
    else{
        // Es el proceso padre
        printf("\nSoy el proceso padre y mi pid es %d", getpid());
        if(entrada%4 == 0)
            printf("\n\tEl número es divisible por 4");
        else
            printf("\n\tEl número no es divisible por 4");
    }

    return 0;
}