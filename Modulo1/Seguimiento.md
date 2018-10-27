# Practicas SO

## Módulo 1

---

### Sesión 1

#### Crear una nueva cuenta de usuario

Usaremos el siguiente comando:

`$ useradd`

Esto creara un nuevo usuario en nuestro sistema y su grupo principal, además de las diferentes entradas por defecto de los archivos `/etc/shadow`, `/etc/passwd` y `/etc/group`. También se crea el directorio de inicio en `/home` y los archivos de configuración por defecto ubicados en este directorio.

##### Actividad 1.2

Ejecutamos 

`$ cat /etc/default/useradd`

y con la salida vemos que por defecto se le asigna el grupo 100, el directorio `/home` y el shell bash.

`$ cat /etc/login.defs`

Al ejecutar esto vemos que cuando hace user add le va asignando a los nuevos usuarios los UID empezando en 500 como mínimo y acabando en 60000 como máximo. Los parámetros de envejecimiento de la cuenta son los siguientes:

+ **Máximos días para lqa contraseña:** 99999
+ **Mínimos días para la contraseña:** 0
+ **Longitud mínima de la contraseña:** 5
+ **Número de días en los que se avisa antes de que expire una contraseña:** 7

#### Modificar valores de una cuenta

`$ usermod` - Modifica una cuenta de usuario

`$ userdel` - Elimina una cuenta de usuario

`$ newusers` - Crea nuevos usuarios con la infromación dada en un archivo de texto con el formato de /etc/passwd

`$ system-config-users` - Herramienta con interfaz gráfica

#### Archivos de configuración del shell

`.bash_profile` - Script que se inicia al iniciar sesión. Aquí podemos definir alias, configuraciones, variables, etc.

`.bashrc` - Es un script igual que el de arriba pero se ejecuta cada vez que se ejecuta la shell

`.bash_logout` - Script como los anteriores que se ejecuta al salir el usuario del sistema.

##### Ejercicio 1.3

1. **Creamos usuarios cambiando valores por defecto:**

`useradd -U -M -p 12345 -r user1`

Con esta instrucción lo que hacemos es crear un usuario llamado `user1` con las siguientes características:

+ `-U` Crea un grupo de usuarios con el mismo nombre del usuario y lo mete dentro.
+ `-M` No crear directorio home
+ `-p` Determinar una contraseña
+ `-r` Crear una cuenta del sistema

Todo esto lo podemos hacer también cambiando la configuración del archivo `/etc/login.defs`. Hay muchas más opciones para crear usuarios que se pueden ver con el comando `man useradd`.

2. **Eliminamos la cuenta y vemos el rastro que ha dejado**

`userdel user1`

En este caso no ha dejado porque no hemos creado la carpeta correspondiente en `/home`, pero normalmente si hubieramos creado la carpeta personal esta no se hubiera borrado.

Podemos eliminar en esta orden directamente el directorio `/home` y sus archivos. Esto lo hacemos con la siguiente orden:

`userdel -r user1`

##### Ejercicio 1.4

El formato de nuestro usuario en el archivo `/etc/passwd` es la siguiente:

`user1:x:500:500::/home/user1:/bin/bash`

El fomato de esta línea es la siguiente:

`usuario:password:UID:GID:descripción:home:shell`

El ejercicio nos pregunta quién es el propietario del archivo `passwd` y cuáles son sus permisos.

Si hacemos `ls -l` en `/etc` en la salida econtramos esta línea:

`-rw-r--r--  1 root root     879 Oct 18 06:58 passwd`

En esta línea podemos ver información del archivo según la columna que miremos:

+ `root` Indica el propietario del archivo
+ `-rw-r--r--` Indica los permisos del archivo

#### Cambio de contraseña de un usuario

Para cambiar la contraseña de cualquier cuenta del equipo, siempre que seamos root, usaremos:

`passwd user1`

##### Ejercicio 1.5

Da error debido que hacen falta permisos de usuario para poder leer este archivo.

#### Parámetros de configuración de la cuenta

Con la orden `chage` podremos acceder y cambiar valores de configuración de un usuario.

#### Gestión de grupos

Un grupo tiene un nombre, un GID y una lista de usuarios.

##### Ejercicio 1.6

Para crear un grupo usamos `groupadd`

Cuando usamos `id` en root, nos devuelve el UID del usuario, el GID, y los grupos a los que pertenece el usuario.

#### Sistema de archivos linux

Las diferentes carpetas del sistema de archivos de linux desenpeñan una función especial.

`/bin` - Almacena programas de utilidad para poder ser usados por cualquier usuario del sistema.

`/sbin` - Programas fundamentales para ser utilizados por el usuario root

`/boot` - Archivos a ejecutar en el arranque del sistema

`/dev` - Archivos de dispositivo

`/etc` - Archivos de configuración de sistema

`/home` - Contiene los directorios personales de los usuarios excepto el de root que se almacena el `/root`

`/lib` - Bibliotecas que se usan para que funcionen los archivos de `/bin` y `/sbin`

`/media` - Directorio que actua como punto de montaje para dispositivos extraibles

`/mnt` - Actua como punto de montaje para dispositivos temporales

`/opt` - Se ubican programas que no forman parte del sistema

`/proc` - Sistema de archivos virtual para hacer de interfaz entre núcleo y procesos

`/tmp` - Archivos temporales que no se mantienen al apagar el sistema

`/usr` - Archivos ejecutables, codigos fuente... Es decir todos los programas ejecutables.

`/var` - Archivos cuyo contenido se espera que cambie durante el funcionamiento del sistema

##### Ejercicio 1.8

Se deberían guardar en la carpeta `/root` ya que esta carpeta es la carpeta de archivos personales de root

#### Información de los SO

Hay dos archivos fundamentales que contienen información de los SO `/etc/fstab` y `/etc/mtab`. Muestran información sobre los sistemas de archivos.

---

### Sesión 2

#### Particiones en discos

##### Ejercicio 2.3

**(a)** Para conseguir que al arrancar el sistema se ejcutara automáticamente `e2fsck` sin que se haya alcanzado el número máximo de montajes sería con la opción `-C` y introduciendole un valor mayor al de `max-mount-counts`.

La opción `-C` lo que hace es establecer un número como el número de veces que el SA ha sido montado.

**(b)** 