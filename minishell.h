#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft_complete/ft_libft/libft.h"







/* ========================================================================= /
/ ESTRUCTURAS DE DATOS CLAVE /
/ ========================================================================= */

// Representa una única redirección (>, <, >>, <<)
ESTRUCTURA t_redireccion {
TIPO_REDIR tipo;    // (p.ej., REDIR_IN, REDIR_OUT, HERE_DOC, APPEND)
CADENA    archivo;  // Nombre del archivo o delimitador (para <<)
}

// Representa un comando simple dentro de una tubería (pipeline)
ESTRUCTURA t_comando {
ARRAY_CADENAS argumentos;  // cmd + args (p.ej., ["ls", "-l", NULL])
LISTA_REDIR redirecciones; // Lista de t_redireccion
ENTERO     fd_entrada;     // Descriptor de archivo de entrada (0 por defecto)
ENTERO     fd_salida;      // Descriptor de archivo de salida (1 por defecto)
}

// Representa el estado global del shell
ESTRUCTURA t_shell_data {
LISTA_CADENAS entorno;       // Lista ligada de variables de entorno (key=value)
ENTERO       last_exit_status; // Variable $? (estado de salida del último comando)
ENTERO       signal_flag;    // Bandera para indicar si se recibió una señal
}

// TIPO_REDIR (ENUM o constantes)
TIPO_REDIR {
REDIR_IN = 0,
REDIR_OUT,
APPEND,
HERE_DOC,
}

/* ------------------------------------------------------------------------- /
/ NOTAS IMPORTANTES DE ESTRUCTURAS /
/ ------------------------------------------------------------------------- */
// 1. La LISTA_CADENAS para el entorno es crítica. Usar una lista facilita la
//    implementación de los built-ins 'export' y 'unset', que modifican el entorno.
// 2. La variable 'last_exit_status' debe ser actualizada después de cada ejecución.
// 3. El ARRAY_CADENAS de argumentos para t_comando es lo que eventualmente
//    se pasará a execve(path, argumentos, entorno).





#endif