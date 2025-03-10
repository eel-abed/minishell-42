/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:18 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/09 17:49:35 by eel-abed         ###   ########.fr       */
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

static void	handle_redir_and_args(t_tokens **current, bool *first)
{
	if ((*current)->type == kind_redir_left
		|| (*current)->type == kind_redir_right
		|| (*current)->type == kind_redir_2left
		|| (*current)->type == kind_redir_2right)
	{
		if ((*current)->next)
			*current = (*current)->next->next;
		else
			*current = NULL;
	}
	else if (!is_valid_n_flag((*current)->value))
	{
		if (*first == false)
			ft_putchar_fd(' ', STDOUT_FILENO);
		else
			*first = false;
		ft_putstr_fd((*current)->value, STDOUT_FILENO);
		*current = (*current)->next;
	}
	else
		*current = (*current)->next;
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
		handle_redir_and_args(&current, &first);
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

static bool	check_echo_command(t_tokens *tokens, t_tokens **current)
{
	bool	found_echo;

	*current = tokens;
	found_echo = false;
	while (*current && !found_echo)
	{
		if (ft_strcmp((*current)->value, "echo") == 0)
			found_echo = true;
		else
			*current = (*current)->next;
	}
	if (!found_echo || !(*current)->next)
		return (false);
	*current = (*current)->next;
	return (true);
}

void	echo_builtin_tokens(t_tokens *tokens)
{
	t_tokens	*current;
	bool		newline;

	newline = true;
	if (!check_echo_command(tokens, &current))
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (current && is_valid_n_flag(current->value))
	{
		newline = false;
		current = current->next;
	}
	print_echo_args(tokens, newline);
}
