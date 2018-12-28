/**
 * Define una macro en lenguaje C que tenga la misma funcionalidad que la macro S_ISREG(mode)
 * usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de la struct 
 * stat, y comprueba que funciona en un programa simple. Consulta en un libro de C o en 
 * internet cómo se especifica una macro con argumento en C.
 */
#include <sys/stat.h>

#define S_ISREG2(mode) (mode & S_IFMT == S_ISREG)