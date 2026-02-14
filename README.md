*This project has been created as part of the 42 curriculum by dperez-p, najlghar.*

# Minishell

## Description
This project is our version of a basic shell, inspired by bash. The main objective was to learn how a terminal works internally, handling processes, file descriptors, and memory.

 The program is capable of:
- Showing a prompt to type commands.
- Searching and executing executables based on the PATH variable.
- Handling single and double quotes.
- Implementing redirections: input (`<`), output (`>`), append (`>>`) and here-doc (`<<`).
- Using pipes (`|`) to connect commands.
- Handling signals like ctrl-C, ctrl-D and ctrl-\.
- Managing environment variables.

Additionally, we have recreated the following builtins:
- `echo` with option -n
- `cd` with a relative or absolute path
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

## Instructions

### Requirements
You need to have the `readline` library installed and a compiler like `cc` or `gcc`.

### Compilation
To compile the project, simply run the `make` command in the terminal inside the project folder:

```bash
make
```

This will create the `minishell` executable.

### Execution
Once compiled, you can start the shell with:

```bash
./minishell
```

```Silencing readline stillrecheable
valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell
```

It works like any other shell, you can try typical commands like `ls -l | grep .c` or navigate through directories.

## Resources

To do this project we have based ourselves on several sources:
- The GNU Bash official manual.
- `man readline` to understand how to read the command line.
- Documentation on system functions `fork`, `execve`, `pipe`, `dup2`.
- Simpleshell tutorial to understand in depth the operation: https://www.youtube.com/watch?v=2xayf6AMNtU&list=PLLT0FgF-zMXPcWHLCsZUl6soZqk59CPHg

### AI Usage
We have used Artificial Intelligence tools (Copilot, ChatGPT) for some tasks:

- **Pseudocode generation** Used to guide the direction of the project by generating pseudocode
and sections.
- **Concept explanation:** To better understand how signal handling and the process execution tree work.
- **Debugging:** To find difficult memory errors or specific segfaults and understand valgrind messages.
- **Documentation generation:** To help draft this README file and structure the information clearly.
