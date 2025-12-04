/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-p <dperez-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:50:39 by dperez-p          #+#    #+#             */
/*   Updated: 2025/12/04 19:14:01 by dperez-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ========================================================================= /
/ PSEUDOCÓDIGO: FLUJO PRINCIPAL (main) /
/ ========================================================================= */

// Variable Global Única (Según el enunciado)
ENTERO G_SIGNAL_NUM = 0; // Solo almacena el número de la señal recibida

FUNCIÓN main(entero argc, array_cadenas argv) {
ESTRUCTURA t_shell_data shell;

// 1. Inicialización
ft_init_shell(&shell, argv);
ft_setup_signal_handlers_interactive(); // Configurar señales para modo interactivo

// 2. Bucle Principal (Mini-Shell Loop)
ft_minishell_loop(&shell);

// 3. Limpieza y Salida
ft_cleanup(&shell);
RETORNAR (shell.last_exit_status);


}

// --- SUB-FUNCIONES ---

FUNCIÓN ft_init_shell(t_shell_data *shell, array_cadenas envp_original) {
// Inicializar el estado del shell
shell->last_exit_status = 0;
shell->signal_flag = 0;

// Clonar el entorno original (envp)
shell->entorno = ft_clone_env(envp_original);

// [NOTA]: En C, usa `tcgetattr` y `tcsetattr` para modificar el terminal
// si es necesario (p.ej., para deshabilitar el eco de teclas), pero
// `readline` ya maneja gran parte de esto.


}

FUNCIÓN ft_minishell_loop(t_shell_data *shell) {
CADENA linea_leida;

MIENTRAS (VERDADERO) {
    // Restaurar terminal y preparar para leer
    ft_restore_terminal_settings(); // Opcional, pero buena práctica si se modificó.

    // Mostrar Prompt (p.ej., "minishell> ") y leer línea
    linea_leida = readline("minishell> ");

    // 1. Manejo de Ctrl-D (EOF)
    SI (linea_leida ES NULO) {
        printf("exit\n");
        BREAK; // Sale del bucle, terminando el shell (como ctrl-D)
    }

    // 2. Procesar línea no vacía
    SI (linea_leida NO ESTÁ VACÍA) {
        add_history(linea_leida);
        ft_process_command(linea_leida, shell);
    }

    free(linea_leida);
}


}

// --- MANEJO DE SEÑALES ---

FUNCIÓN ft_setup_signal_handlers_interactive() {
// ctrl-C: Imprime nueva entrada en línea nueva (comportamiento de bash)
// ctrl-: Ignorar (comportamiento de bash)

// Usar sigaction es más robusto y permite evitar la "trampa" del manejo de señales
// en funciones no asíncronas seguras.
ESTRUCTURA sigaction sa_int, sa_quit;

// Configurar SIGINT (Ctrl-C)
sa_int.sa_handler = &ft_signal_handler_interactive;
sigemptyset(&sa_int.sa_mask);
sa_int.sa_flags = SA_RESTART;
signal(SIGINT, &sa_int, NULL);

// Configurar SIGQUIT (Ctrl-\)
sa_quit.sa_handler = SIG_IGN; // IGNORAR
signal(SIGQUIT, &sa_quit, NULL);


}

FUNCIÓN ft_signal_handler_interactive(entero signal_num) {
// SOLO establece la variable global (regla del proyecto)
G_SIGNAL_NUM = signal_num;

// Comportamiento de Ctrl-C interactivo (fuera de un comando en ejecución)
IF (signal_num == SIGINT) {
    // Escribir nueva línea y prompt, sin tocar estructuras de datos
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
// [NOTA]: SIGQUIT (Ctrl-\) se ignora, como se configuró en ft_setup_signal_handlers_interactive.


}

/* ------------------------------------------------------------------------- /
/ NOTAS IMPORTANTES DE FLUJO PRINCIPAL /
/ ------------------------------------------------------------------------- */
// 1. Ctrl-D (EOF): readline retorna NULL. Esto es la señal para llamar a 'exit' y terminar.
// 2. Ctrl-C (SIGINT): Cuando no hay un proceso hijo ejecutándose, debe forzar una nueva línea
//    y redisplay del prompt. Esto se maneja en el ft_signal_handler_interactive.
// 3. Variable Global: La variable G_SIGNAL_NUM debe ser el único punto de contacto
//    entre el gestor de señales y el resto del código. No debe ser una estructura.