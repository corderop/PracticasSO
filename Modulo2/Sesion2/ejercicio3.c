/**
   Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a
   partir de uno dado como argumento y devuelva la cuenta de todos aquellos archivos 
   regulares que tengan permiso de ejecución para el grupo y para otros. Además del 
   nombre de los archivos encontrados, deberá devolver sus números de inodo y la 
   suma total de espacio ocupado por dichos archivos. El formato de la nueva orden 
   será:
      
        $> ./buscar <pathname>
  
   donde <pathname> especifica la ruta del directorio a partir del cual queremos que
   empiece a analizar la estructura del árbol de subdirectorios. En caso de que no se 
   le de argumento, tomará como punto de partida el directorio actual. Ejemplo de la 
   salida después de ejecutar el programa:

        Los i-nodos son:
        ./a.out 55
        ./bin/ej 123
        ./bin/ej2 87
        ...
        Existen 24 archivos regulares con permiso x para grupo y otros
        El tamaño total ocupado por dichos archivos es 2345674 bytes

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

int procesarArchivo(struct stat metadatos){
     int salida = 0;

     if( ((S_IXOTH & metadatos.st_mode) != 0) && ((S_IXGRP & metadatos.st_mode) != 0) ) {
          salida = 1;
     }   

     return salida;
}

int recorrerDirectorio(char *pathname, int *archivosConPermisos){
     DIR *dir;
     struct dirent *estructura;
     struct stat metadatos;
     char cadena[50];
     long int totalTamano = 0;

     dir = opendir(pathname);
     while((estructura=readdir(dir)) != NULL){
          if(strcmp(estructura->d_name,".") != 0 && strcmp(estructura->d_name,"..") != 0){
               sprintf(cadena,"%s/%s", pathname, estructura->d_name);
               if(stat(cadena, &metadatos)<0){
               printf("\nError al intentar acceder a los atributos de %s", cadena);
               perror("\nError en stat");
               exit(-1);
               }
               if(S_ISDIR(metadatos.st_mode)){
                    totalTamano += recorrerDirectorio(cadena, archivosConPermisos);
               }
               else{
                    *archivosConPermisos += procesarArchivo(metadatos);
                    totalTamano += metadatos.st_size;
                    printf("\n./%s %ld", cadena, metadatos.st_size);
               }
          }
     }

     closedir(dir);
     return totalTamano;
}

int main(int argc, char* argv[]){
     DIR *principal;
     struct dirent *estructura;
     struct stat metadatos;
     char cadena[50];
     char *pathname;
     long int totalTamano = 0;
     int conPermiso = 0;

     if(argc != 2){
          printf("Forma errónea de introducir los datos. Forma correcta: \n\t./programa <pathname>");
          exit(-1);
     }
     else
          pathname = argv[1];

     principal = opendir(pathname);
     readdir(principal);
     readdir(principal);
     while((estructura=readdir(principal)) != NULL){
          if(strcmp(estructura->d_name,".") != 0 && strcmp(estructura->d_name,"..") != 0){
               sprintf(cadena,"%s/%s", pathname, estructura->d_name);
               if(stat(cadena, &metadatos)<0){
               printf("\nError al intentar acceder a los atributos de %s", cadena);
               perror("\nError en stat");
               exit(-1);
               }
               if(S_ISDIR(metadatos.st_mode)){
                    totalTamano += recorrerDirectorio(cadena, &conPermiso);
               }
               else{
                    conPermiso += procesarArchivo(metadatos);
                    totalTamano += metadatos.st_size;
                    printf("\n./%s %ld", cadena, metadatos.st_size);
               }
          }
     }

     closedir(principal);

     printf("\nExisten %i archivos regulares con permiso x para grupo y otros",conPermiso);
     printf("\nEl Tamano total ocupado por dichos archivos es %ld bytes",totalTamano);

     return 0;
}