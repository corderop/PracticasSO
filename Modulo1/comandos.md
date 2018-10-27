# Comandos

## Gestión de usuarios

---

### Crear usuario

`useradd` - Crea un usuario con la configuración por defecto de los archivos `$ cat /etc/default/useradd` y `$ cat /etc/login.defs`

**Parámetros**

`-b` - Sirve para especificar el directorio donde queremos crear la carpeta principal del usuario, con el nombre por defecto.

`-d` - Sirve para especificar el directorio y el nombre de la carpeta principal del usuario.

`-e` - Crear el usuario con fecha de expiración en la cual el usuario se desactivará. Se especifíca con el formato AAAA-MM-DD.

`-f` - El número de dias que pasan para que la constraseña expire por desuso. El valor -1 desactiva esta opción.

`-g` - Se especifica el grupo por su número o nombre. El grupo a asignar debe de existir.

`-G` - Grupos suplementarios a los que pertenecerá este usuario.

`-k` - Copia los archivos especificados en la carpeta principal del usuario.

`-m` - Crea el home del usuario si este no existe.

`-M` - No crea carpeta principal.

`-N` - No crea un grupo con el mismo nombre del usuario.

`-o` - Permite crear usuarios con un UID duplicado.

`-p` - Crea una contraseña para el usuario.

`-r` - Crea una cuenta del sistema. No crea carpeta principal, tienes que especificarlo aparte.

`-s` - Para cambiar el usuario para acceder en la shell

`-u` - El valor númerico que le quieres dar al usuario.

`-U` - Crea un grupo con el mismo nombre que el usuario y lo mete dentro.

---

### Modificar usuario

`usermod` - Sirve para modificar usuarios. Los parametros son practicamente los mismos que los del comando anterior.

---

### Eliminar usuario

`userdel` - Elimina un usuario

**Parámetros**

`-f` - Forzar la eliminación

`-r` - Elimina la carpeta principal del usuario y sus archivos.

---

### Información de los usuarios del sistema

**`cat /etc/shadow`**

Formato de salida:

`nombre : password cifrado : dias desde cambio de contraseña : dias validez cuenta : dias de aviso antes de caducar la contraseña : dias para deshabilitar la cuenta tras caducación de password : fecha de caducidad`

**`cat /etc/passwd`**

Formato de salida:

`nombre : password : uid : gid : descripcion : home : shell`

**`cat /etc/group`**

Formato de salida:

`nombre : password : gid : miembros`

---

### Archivos de configuración del shell

`.bash_profile` - Script que se inicia al iniciar sesión. Aquí podemos definir alias, configuraciones, variables, etc.

`.bashrc` - Es un script igual que el de arriba pero se ejecuta cada vez que se ejecuta la shell

`.bash_logout` - Script como los anteriores que se ejecuta al salir el usuario del sistema.

---

### Cambiar parámetros usuario

`chage` - Sirve para establecer las restricciones de tiempo de un usuario.

**Parámetros**

`-d` - Fecha del último cambio de password

`-m` - Número de días que deben pasar para poder cambiar la contraseña

`-M` - Número de días que se puede estár con la misma contraseña sin cambiarla

`-W` - Antelación con la que se avisará antes de que la contraseña expire

`-I` - Número de dias despúes de que la contraseña expire, cuando la cuenta se deshabilite de forma automática

`-E` - Fecha en la que la cuenta expira

---

## Gestión de grupos

---

`groupadd` - Crea un nuevo grupo

**Parámetros**

`-f` - Forzar la creación

`-g` - Cambia el GID

`-o` - Permite añadir un grupo sin una id única

`-p` - Establece una contraseña al grupo

`-r` - Crea un grupo del sistema

---

`groupmod` - Modifica un grupo existente

Los parametros son parecidos a los de `grupoadd`

---

`groupdel` - Elimina un grupo

---

`newgrp` - Cambia de grupo activo. Lanza una shell con ese grupo

---

`gpasswd` - Asigna una contraseña al grupo

**Parametros**

`-a` - Añade un usuario al grupo

`-d` - Elimina un usuario del grupo

`-r` - Elimina la contraseña del grupo

`-R` - Restringe el acceso al grupo(se tiene que usar la contraseña para acceder con `newgrp`)

`-A` - Se modifica la lista de administradores del grupo

`-M` - Se modifica la lista de miembros del grupo

---

`groups` - Informa de los grupos a los que pertenece un usuario.

---

`id` - Lista el indentificador del usuario y los grupos a los que pertenece

---

`grpck` - Comprueba la consistencia del archivo de grupos

---

## Gestión de archivos

`pwd` - Muestra el directorio actual

`ls` - Muestra los archivos actuales

`cd` - Cambia la ruta de trabajo

`mkdir` - Crea un nuevo directorio

`rmdir` - Elimina un directorio

`cat` - Muestra el contenido de un archivo

`rm` - Elimina un archivo

`cp` - Copia un archivo

`mv` - Mueve un archivo

`chmod` - Modifica los permisos de un archivo

`touch` - Crea o cambia la fecha de un archivo

---

## Gestión de discos

---

### Creación de dispositivos simulados

---

`mknod` - Lo usaremos para crear un archivo de bloque que luego enlazaremos con un dispositivo simulado. Usaremos el siguiente formato:

`mknod opciones ruta tipo major menor`

Para crear un dispositivo simulado usaremos el comando

`mknod /dev/nombre b 7 0-1-2...`

Usamos el tipo `b` porque es de tipo bloque, `7` porque queremos ese tipo de archivo

---

`dd` - La usaremos para crear archivos que posterior mente asociaremos con el dispositivo.

**Parámetros**

`if=` - Aquí indicaremos de donde leeremos el archivo para crear el archivo

`of=` - Archivo en el que se tiene que escribir lo que creamos

`bs=` - Bytes de lectura y escritura en un tiempo

`count=` - Numero de bloques de entrada que se copian

Para crear el archivo usamos:

`dd if=/dev/zero of=/root/archivo20 bs=2k count=10000`

Así creamos un archivo de 20 MB vacío porque el `if=` es `/dev/zero`

Con este comando lo que se hará es copiar 10000 veces `/dev/zero` en `/root/archivo20` 2k bytes.

---

`losetup` - Sirve para asociar un dispositivo con una ruta.

Lo usaremos de la siguiente forma:

`losetup /dev/loop0 /root/archivo20`

---

### Particionar un disco

`fdisk` - Para particionar un disco y realizar diferentes acciones sobre un disco

Lo usaremos de la siguiente forma:

`fdisk /dev/disco`

---

### Formatear lógicamente una partición

Una vez tenemos creadas la particiones principales, formateamos logicamente las particiones:

`mke2fs` - Formateamos lógicamente las particiones

En este caso para formatear con los formatos `etx3` y `etx4`, lo hacemos de la siguiente forma:

`mkfs.ext3 -L 'LABEL_ext3' /dev/loop0`

`mkfs.ext4 -L 'LABEL_ext4' /dev/loop1`

---

### Ajuste de parámetros configurables y comprobación de errores

`tune2fs` - Ajustar parámetros y visualización de estos

**Parámetros**

`-l` - Muestra por pantalla información del SA

`-c` - Se establece el número máximo de montajes que se podrán llegar a hacer sin realizar una comprobación de consistencia. Se usará de la siguiente forma:

`tune2fs -c numero <dispositivo>`

`-L` - Poner una etiqueta al SA. Se usa de la siguiente forma

`tune2fs -L etiqueta <dispositivo>`

---

### Administración y reparación de la metainformación

`fsck` - Sirve para ejecutar manualmente comprobaciones y reparar inconsistencias del SA.

---
