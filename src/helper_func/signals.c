/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:52:25 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 14:33:19 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc_sig_handler(int sig);

void	handle_sigint(int sig)
{
	g_signal_received = sig;
	if (sig == SIGINT)
	{
		printf("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_signal_received < 0)
	{
		g_signal_received = sig;
	}
	else
	{
		rl_on_new_line();
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

void	setup_here_doc_signals(void)
{
	struct sigaction	sa_int;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = here_doc_sig_handler;
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
}

void fork_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}


void wait_pid_handler(int sig)
{
	g_signal_received = sig;
	printf("\n");
}

void wait_pid_signals(void)
{
	signal(SIGINT, wait_pid_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
