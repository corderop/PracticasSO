/**
    Escribe un programa que acepte como argumentos el nombre de un programa, sus
    argumentos si los tiene, y opcionalmente la cadena “bg”. Nuesto programa deberá 
    ejecutar el programa pasado como primer argumento en foreground si no se 
    especifica la cadena “bg” y en background en caso contrario. Si el programa 
    tiene argumentos hay que ejecutarlo con éstos

    NO COMPROBADO EL CORRECTO FUNCIONAMIENTO
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

int buscar(int argc, char* argv[]){
    int salida = -1;

    for(int i=0; i<argc && salida==-1; i++){
        if(strcmp(argv[i],"bg")==0)
            salida = i;
    }

    return salida;
}

int main(int argc, char* argv[]){
    pid_t pid;
    int encontrado = buscar(argc, argv),
        estado;
    char *salida[argc-3];

    if(argc<2){
        perror("Entrada no valida");
        exit(-1);
    }else{
        if(encontrado != -1){
            if((pid = fork())<0){
                perror("Fallo en el fork");
                exit(-1);
            }
            else{
                if(pid==0){
                    for(int i=1; i<encontrado; i++)
                        strcpy(salida[i-1],argv[i]);
                    execv(argv[1], salida);
                }
            }
        }
    }
    wait(&estado);

    return 0;
}