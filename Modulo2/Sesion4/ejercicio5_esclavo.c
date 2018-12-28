#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<math.h>

int esPrimo(int n){
    int i;
    int limite = sqrt(n);
    int es_primo = 1;

    for (i = 2; i <= limite && es_primo; i++)
        if (n % i == 0)
            es_primo = 0;

    return es_primo;
}

int main(int argc, char*argv[]){
    int int_sup,
        int_inf;

    if(argc != 3){
        perror("Parámetros erroneos:\n\n\t./programa <intervalo-inf> <intervalo-sup>");
        exit(-1);
    }else{
        int_inf = strtol(argv[1],NULL, 10);
        int_sup = strtol(argv[2],NULL, 10);
        if(int_sup<=int_inf){
            perror("Intervalo erroneo:\n\n\t./programa <intervalo-inf> <intervalo-sup>");
            exit(-1);
        }
    }

    if(setvbuf(stdout,NULL,_IONBF,0)){    
        perror("\nError en setvbuf");
    }

    for(int i=int_inf ; i<=int_sup; i++){
        if(esPrimo(i))
            write(STDOUT_FILENO, &i,sizeof(int));
    }

    return EXIT_SUCCESS;
}