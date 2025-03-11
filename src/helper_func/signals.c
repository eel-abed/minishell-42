/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:52:25 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/11 16:01:57 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
void here_doc_sig_handler(int sig);

void	handle_sigint(int sig)
{
    g_signal_received = sig;
    if (sig == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0); // Clear the current input line
        rl_on_new_line();
        rl_redisplay();
    }
}

void handle_sigquit(int sig)
{
    (void)sig;

    // We don't write anything here - the message will be printed
    // when we detect that a child process was terminated by SIGQUIT
    if (g_signal_received < 0) {
        // Signal received during command execution
        g_signal_received = sig;
    } else {
        // At prompt, just redisplay without the ^\ characters
        rl_on_new_line();
        rl_redisplay();
    }
}

void	setup_signals(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
}

void	setup_here_doc_signals(void)
{
	struct sigaction	sa_int;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = here_doc_sig_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
}
