/**
    Implementa un programa que lance cinco procesos hijo. Cada uno de ellos se identificará en la 
    salida estándar, mostrando un mensaje del tipo "Soy el hijo PID". El proceso padre simplemente 
    tendrá que esperar la finalización de todos sus hijos y cada vez que detecte la finalización 
    de uno de sus hijos escribirá en la salida estándar un mensaje del tipo:
        
        Acaba de finalizar mi hijo con <PID>
        Sólo me quedan <NUM_HIJOS> hijos vivos
*/

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int estado;

    for(int i=0; i<5; i++){
        pid_t pid;
        if((pid=fork()) < 0){
            perror("\nError en el fork\n");
	        exit(EXIT_FAILURE);
        }else{
            if(pid==0){
                printf("\nSoy el hijo %d\n", getpid());
                exit(0);
            }
        }
    }

    for(int i=4; i>=0; i--){
        pid_t pid = wait(&estado);
        printf("\nAcaba de finalizar mi hijo con PID: %d\n", pid);
        printf("\nSolo me quedan %d hijos vivos\n", i);
    }

    return 0;
}