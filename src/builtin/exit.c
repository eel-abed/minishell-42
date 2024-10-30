/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:56 by eel-abed          #+#    #+#             */
/*   Updated: 2024/10/22 16:16:17 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void exit_builtin(char **args)
{
    (void)args;
	printf("exit command executed\n");
}

/*
void	exit_builtin(char **args)
{
	if (args[1])
	{
		printf("minishell: exit: too many arguments\n");
		return;
	}
	printf("exit\n");
	exit(g_exit_status);
}
*/
