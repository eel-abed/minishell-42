/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:40 by eel-abed          #+#    #+#             */
/*   Updated: 2024/10/23 16:05:25 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_builtin(void)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
	{
		ft_putendl_fd(*env, STDOUT_FILENO);
		env++;
	}
}
