/**
    Este ejercicio se basa en la idea de utilizar varios procesos para realizar partes de una
    computación en paralelo. Para ello, deberá construir un programa que siga el esquema de
    computación maestro-esclavo, en el cual existen varios procesos trabajadores (esclavos)
    idénticos y un único proceso que reparte trabajo y reúne resultados (maestro). Cada esclavo es
    capaz de realizar una computación que le asigne el maestro y enviar a este último los resultados
    para que sean mostrados en pantalla por el maestro.

    El ejercicio concreto a programar consistirá en el cálculo de los números primos que hay en un
    intervalo. Será necesario construir dos programas, maestro y esclavo. Ten en cuenta la
    siguiente especificación:

        1. El intervalo de números naturales donde calcular los número primos se pasará como
        argumento al programa maestro. El maestro creará dos procesos esclavos y dividirá el
        intervalo en dos subintervalos de igual tamaño pasando cada subintervalo como
        argumento a cada programa esclavo. Por ejemplo, si al maestro le proporcionamos el
        intervalo entre 1000 y 2000, entonces un esclavo debe calcular y devolver los números
        primos comprendidos en el subintervalo entre 1000 y 1500, y el otro esclavo entre 1501
        y 2000. El maestro creará dos cauces sin nombre y se encargará de su redirección para
        comunicarse con los procesos esclavos. El maestro irá recibiendo y mostrando en
        pantalla (también uno a uno) los números primos calculados por los esclavos en orden
        creciente.

        2. El programa esclavo tiene como argumentos el extremo inferior y superior del intervalo
        sobre el que buscará números primos. Para identificar un número primo utiliza el
        siguiente método concreto: un número n es primo si no es divisible por ningún k tal que
        2 < k <= sqrt(n), donde sqrt corresponde a la función de cálculo de la raíz cuadrada
        (consulte dicha función en el manual).
        El esclavo envía al maestro cada primo
        encontrado como un dato entero (4 bytes) que escribe en la salida estándar, la cuál se
        tiene que encontrar redireccionada a un cauce sin nombre. Los dos cauces sin nombre
        necesarios, cada uno para comunicar cada esclavo con el maestro, los creará el maestro
        inicialmente. Una vez que un esclavo haya calculado y enviado (uno a uno) al maestro
        todos los primos en su correspondiente intervalo terminará.

*/
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char*argv[]){
    pid_t   esclavo1,
            esclavo2;
    int     fd1[2],
            fd2[2],
            int_inf,
            pto_medio,
            int_sup,
            val1,
            val2;
    char    c_pto_medio[50],
            c_pto_medio_2[50];

    if(argc != 3){
        perror("Parámetros erroneos:\n\n\t./programa <intervalo-inf> <intervalo-sup>");
        exit(-1);
    }else{
        int_inf = strtol(argv[1],NULL, 10);
        int_sup = strtol(argv[2],NULL, 10);
        pto_medio = (int_sup-int_inf)/2 + int_inf;
        sprintf(c_pto_medio,"%d",pto_medio);
        sprintf(c_pto_medio_2,"%d",pto_medio+1);
        if(int_sup<=int_inf){
            perror("Intervalo erroneo:\n\n\t./programa <intervalo-inf> <intervalo-sup>");
            exit(-1);
        }
    }
    
    pipe(fd1);

    if((esclavo1=fork())<0){
        perror("Creación de esclavo 1");
        exit(-1);
    }

    if(esclavo1==0){
        close(fd1[0]);

        //Duplicar el descriptor de escritura en cauce en el descriptor
        //correspondiente a la salida estandar (stdout)
        dup2(fd1[1],STDOUT_FILENO);
        if(execl("./Sesion4/esclavo_exe","esclavo_exe",argv[1],c_pto_medio,NULL)<0){
            perror("ejecucion");
            exit(-1);
        }
    }
    else{
        //Establecer la direcci�n del flujo de datos en el cauce cerrando
		// el descriptor de escritura en el cauce del proceso padre.
		close(fd1[1]);

		//Duplicar el descriptor de lectura de cauce en el descriptor
		//correspondiente a la entrada est�ndar (stdin)
        printf("Valores primos del intervalo [%d,%d]:\n", int_inf, pto_medio);
		while(read(fd1[0],&val1,sizeof(int))>0){
            printf("%d, ",val1);
        }
        close(fd1[0]);
    }

    pipe(fd2);

    if((esclavo2=fork())<0){
        perror("Creación de esclavo 2");
        exit(-1);
    }

    if(esclavo2==0){
        close(fd2[0]);

        //Duplicar el descriptor de escritura en cauce en el descriptor
        //correspondiente a la salida estandar (stdout)
        dup2(fd2[1],STDOUT_FILENO);
        if(execl("./Sesion4/esclavo_exe","esclavo_exe",c_pto_medio_2, argv[2],NULL)<0){
            perror("ejecucion");
            exit(-1);
        }
    }
    else{
        close(fd2[1]);
        printf("\nValores primos del intervalo [%d,%d]:\n", pto_medio+1, int_sup);
		while(read(fd2[0],&val2,sizeof(int))>0){
            printf("%d, ",val2);
        }
        close(fd2[0]);
    }

    return EXIT_SUCCESS;
}