/**
    Implementa una modificación sobre el anterior programa en la que el proceso padre 
    espera primero a los hijos creados en orden impar (1o,3o,5o) y después a los hijos 
    pares (2o y 4o)
*/
#include<sys/types.h>
#include<unistd.h>		
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int estado,
        contador = 5;
    pid_t pid[5];

    for(int i=0; i<5; i++){
        if((pid[i]=fork()) < 0){
            perror("\nError en el fork\n");
	        exit(EXIT_FAILURE);
        }else{
            if(pid[i]==0){
                printf("\nSoy el hijo %d\n", getpid());
                exit(0);
            }
        }
    }

    // Impares
    for(int i=0; i<5; i+=2){
        waitpid(pid[i]);
        printf("\nAcaba de finalizar mi hijo con PID: %d\n", pid[i]);
        contador--;
        printf("\nSolo me quedan %d hijos vivos\n", contador);
    }
    // Pares
    for(int i=1; i<5; i+=2){
        waitpid(pid[i]);
        printf("\nAcaba de finalizar mi hijo con PID: %d\n", pid[i]);
        contador--;
        printf("\nSolo me quedan %d hijos vivos\n", contador);
    }

    return 0;
}