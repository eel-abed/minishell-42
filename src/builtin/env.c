/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:40 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/05 13:39:55 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_builtin(void)
{
	char		**env;

	env = environ;
	while (*env)
	{
		ft_putendl_fd(*env, STDOUT_FILENO);
		env++;
	}
}
