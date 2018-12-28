/**
    Escribe un programa que suspenda la ejecución del proceso actual hasta que se
    reciba la señal SIGUSR1. Consulta en el manual en línea sigemptyset para conocer las distintas
    operaciones que permiten configurar el conjunto de señales de un proceso.
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    sigset_t new_mask;

    // Inicializa un signal set
    sigemptyset(&new_mask);

    // Llena un set con todas las máscaras, es decir no se podrá ejecutar 
    // ninguna de ellas
    sigfillset(&new_mask);

    // Se elimina la máscara SIGUSR1, por lo que esta podrá ejecutarse
    sigdelset(&new_mask,SIGUSR1);

    // Se espera a que se ejecute cualquiera de las máscaras
    sigsuspend(&new_mask);

    return 0;
}