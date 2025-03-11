/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:52:25 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/11 16:10:38 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	if (g_signal_received < 0)
	{
		g_signal_received = sig;
	}
	else
	{
		g_signal_received = sig;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct sigaction	sa_tstp;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
	sa_tstp.sa_handler = SIG_IGN;
	sigemptyset(&sa_tstp.sa_mask);
	sa_tstp.sa_flags = SA_RESTART;
	sigaction(SIGTSTP, &sa_tstp, NULL);
}
