/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:18 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/08 12:41:21 by mafourni         ###   ########.fr       */
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
	bool		found_echo;

	current = tokens;
	first = true;
	found_echo = false;
	while (current && !found_echo)
	{
		if (ft_strcmp(current->value, "echo") == 0)
			found_echo = true;
		current = current->next;
	}
	while (current)
	{
		// Skip the redirection operator and its argument
		if (current->type == kind_redir_left
			|| current->type == kind_redir_right
			|| current->type == kind_redir_2left
			|| current->type == kind_redir_2right)
			current = current->next ? current->next->next : NULL;
		else if (!is_valid_n_flag(current->value))
		{
			if (!first)
				ft_putchar_fd(' ', STDOUT_FILENO);
			else
				first = false;
			ft_putstr_fd(current->value, STDOUT_FILENO);
			current = current->next;
		}
		else
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
	current = current->next;
	while (current && is_valid_n_flag(current->value))
	{
		newline = false;
		current = current->next;
	}
	print_echo_args(tokens, newline);
}
