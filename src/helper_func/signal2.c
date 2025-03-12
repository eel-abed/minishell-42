/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:30:37 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 17:30:45 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_pid_handler(int sig)
{
	g_signal_received = sig;
	printf("\n");
}

void	wait_pid_signals(void)
{
	signal(SIGINT, wait_pid_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
