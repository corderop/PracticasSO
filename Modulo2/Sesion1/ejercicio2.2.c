/**
 * Modificación adicional. ¿Cómo tendrías que modificar el programa para que una vez
 * finalizada la escritura en el archivo de salida y antes de cerrarlo, pudiésemos indicar en su
 * primera línea el número de etiquetas ''Bloque i'' escritas de forma que tuviese la siguiente
 * apariencia?:
 * 
 *  El número de bloques es <no_bloques>
 *  Bloque 1
 *  // Aquí van los primeros 80 Bytes del archivo pasado como argumento.
 *  Bloque 2
 *  // Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
 *  ...
 */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>


int main(int argc, char *argv[]){
    char* entrada;
    char cadena[30];
    char caracter[1];
    char salida[] = "salida.txt";
    int fd_entrada,
        fd_salida;

    // Comprobación de que se ha pasado un parámetro
    if( argc == 2)
        fd_entrada = open(argv[1], O_RDONLY, S_IRUSR);
    else
        fd_entrada = STDIN_FILENO;

    if( (fd_salida = open(salida, O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR|S_IWUSR)) < 0 ){
        printf("\nError %d en open salida",errno);
        perror("\nError en open en salida");
        exit(-1);
    }

    int i=0,
        num_bloques=1;

    while(read(fd_entrada,caracter,1)!=0){
        if(i%80 == 0){
            if(i==0){
                sprintf(cadena, "El conjunto de bloques es: %d", num_bloques-1);
                write(fd_salida, cadena, strlen(cadena));
            }
            sprintf(cadena, "\n%s%d\n", "Bloque", num_bloques++);
            write(fd_salida, cadena, strlen(cadena));
        }

        write(fd_salida, caracter, 1);
        i++;
    }
    lseek(fd_salida, 0, SEEK_SET);
    sprintf(cadena, "El conjunto de bloques es: %d\n", num_bloques-1);
    write(fd_salida, cadena, strlen(cadena));

    close(fd_salida);
    close(fd_entrada);
    return 0;
}