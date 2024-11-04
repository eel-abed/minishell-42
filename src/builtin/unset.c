/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:54:48 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/04 17:31:13 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void unset_builtin(char **args)
{
	int i = 1;
	int j;
	extern char **environ;

	while (args[i])
	{
		j = 0;

		while (environ[j])
		{
			if (strncmp(environ[j], args[i], strlen(args[i])) == 0 && environ[j][strlen(args[i])] == '=')
			{
				while (environ[j])
				{
					environ[j] = environ[j + 1];
					j++;
				}
				break;
			}
			j++;
		}
		i++;
	}
}
