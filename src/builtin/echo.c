/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:18 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/05 17:35:47 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_valid_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	print_echo_args(t_tokens *tokens, bool newline)
{
	t_tokens	*current;
	bool		first;

	current = tokens;
	first = true;
	while (current && current->type != kind_pipe)
	{
		if (ft_strcmp(current->value, "echo") != 0)
		{
			if (!first)
				ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			first = false;
		}
		current = current->next;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	echo_builtin_tokens(t_tokens *tokens)
{
	t_tokens	*current;
	bool		newline;
	bool		found_echo;

	current = tokens;
	newline = true;
	found_echo = false;
	// Find the echo command in tokens
	while (current && !found_echo)
	{
		if (ft_strcmp(current->value, "echo") == 0)
			found_echo = true;
		else
			current = current->next;
	}
	if (!found_echo || !current->next)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	// Check for -n flag
	current = current->next;
	while (current && is_valid_n_flag(current->value))
	{
		newline = false;
		current = current->next;
	}
	// Print arguments
	print_echo_args(tokens, newline);
}
