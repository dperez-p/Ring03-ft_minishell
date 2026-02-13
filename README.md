*Este proyecto ha sido creado como parte del currículo de 42 por dperez-p, najlghar.*

# Minishell

## Descripción
Este proyecto es nuestra version de una shell basica, inspirada en bash. El objectivo principal era aprender como funciona una terminal por dentro, manejando procesos, file descriptors y memoria.

El programa es capaz de:
- Mostrar un prompt para escribir comandos.
- Buscar y ejecutar ejecutables basandose en la variable PATH.
- Manejar comillas simples y dobles.
- Implementar redirecciones: input (`<`), output (`>`), append (`>>`) y here-doc (`<<`).
- Usar tuberias (`|`) para conectar comandos.
- Manejar señales como ctrl-C, ctrl-D y ctrl-\.
- Gestionar variables de entorno.

Ademas, hemos recreado los siguientes builtins:
- `echo` con la opcion -n
- `cd` con ruta relativa o absoluta
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

## Instrucciones

### Requisitos
Necesitas tener instalada la libreria `readline` y un compilador como `cc` o `gcc`.

### Compilación
Para compilar el proyecto, simplemente ejecuta el comando `make` en la terminal dentro de la carpeta del proyecto:

```bash
make
```

Esto creará el ejecutable `minishell`.

### Ejecución
Una vez compilado, puedes iniciar la shell con:

```bash
./minishell
```

Funciona como cualquier otra shell, puedes probar comandos tipicos como `ls -l | grep .c` o navegar por directorios.

## Recursos

Para hacer este proyecto nos hemos vasado en varias fuentes:
- El manual oficial de GNU Bash.
- `man readline` para entender como leer la linea de comandos.
- Documentacion sobre las funciones de sistema `fork`, `execve`, `pipe`, `dup2`.

### Uso de IA
Hemos utilizado herramientas de Inteligencia Artificial (Copilot, ChatGPT) para algunas tareas:
- **Explicación de conceptos:** Para entender mejor como funciona la gestion de señales y el arbol de ejecucion de procesos.
- **Debugging:** Para encontrar errores dificiles de memoria o segfaults puntuales y entender los mensajes de valgrind.
- **Generación de documentación:** Para ayudar a redactar este archivo README y estructurar la informacion de forma clara.
