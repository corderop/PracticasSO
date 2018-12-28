/**
 * Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte 
 * como entrada:
 *  · Un argumento que representa el 'pathname' de un directorio.
 *  · Otro argumento que es un número octal de 4 dígitos (similar al que se puede utilizar
 *    para cambiar los permisos en la llamada al sistema chmod). Para convertir este argumento 
 *    tipo cadena a un tipo numérico puedes utilizar la función strtol. Consulta el manual en
 *    línea para conocer sus argumentos.
 * 
 * El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los
 * permisos de todos los archivos que se encuentren en el directorio indicado en el primer 
 * argumento.
 * 
 * El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio
 * que esté formada por:
 *      
 *      <nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>
 * 
 * Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente
 * información en la línea de salida:
 * 
 *      <nombre_de_archivo> : <errno> <permisos_antiguos>
 */
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

// struct dirent {
//     long d_ino; /* número i-nodo */
//     char d_name[256]; /* nombre del archivo */
// };



int main(int argc, char *argv[]){
    int num_octal;
    DIR *dp;
    struct dirent *estructura;
    struct stat metadatos1;
    char cadena[20];

    if(argc != 3){
        printf("Argumentos mal introducidos.\nIntroducir de la siguiente forma:\nprogrma <filepath> <num_octal>");
        exit(-1);
    }
    else{
        num_octal = strtol(argv[2], NULL, 8);
    }

    dp = opendir(argv[1]);
    while((estructura = readdir(dp)) != NULL){
        sprintf(cadena,"%s/%s", argv[1], estructura->d_name);
        if(stat(cadena, &metadatos1)<0){
            printf("\nError al intentar acceder a los atributos de %p", cadena);
            perror("\nError en stat");
            exit(-1);
        }
        if(S_ISREG(metadatos1.st_mode)){
            if( chmod(cadena, num_octal)<0 ){
                printf("\n%s : %d %o",estructura->d_name,errno, metadatos1.st_mode);
            }
            else{
                printf("\n%s : %o %o",estructura->d_name, metadatos1.st_mode, num_octal);
            }
        }
    }

    closedir(dp);
    return 0;
}