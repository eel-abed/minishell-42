/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:18 by eel-abed          #+#    #+#             */
/*   Updated: 2024/10/22 17:19:12 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo_builtin(char **args)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
/*
static bool	is_valid_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (i > 1);  // Vérifie qu'il y a au moins un 'n' après le '-'
}

void	echo_builtin(char **args)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	// Traite tous les flags -n consécutifs
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = false;
		i++;
	}
	// Écrit les arguments
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}
*/
