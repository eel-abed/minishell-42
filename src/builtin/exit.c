/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:56 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/04 19:21:36 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_builtin(char **args)
{
	int			exit_status;
	char		*endptr;
	long		status;
	const char	*error_msg;

	if (args[1] == NULL)
	{
		exit_status = 0;
	}
	else
	{
		status = strtol(args[1], &endptr, 10);
		if (*endptr != '\0' || endptr == args[1] || status < 0 || status > 255)
		{
			error_msg = "minishell: exit: numeric argument required\n";
			write(STDERR_FILENO, error_msg, strlen(error_msg));
			exit_status = 1;
		}
		else
		{
			exit_status = (int)(status % 256);
		}
	}
	write(STDOUT_FILENO, "exit\n", 6);
	exit(exit_status);
}
