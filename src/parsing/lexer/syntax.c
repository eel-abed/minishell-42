/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:57:47 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/18 19:44:32 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	is_valid_redir_left(char *string, size_t remaining)
{
	size_t	i;
	size_t	redir_left_count;

	i = 1;
	redir_left_count = 1;
	while (i < remaining && string[i] == '<')
	{
		redir_left_count += 1;
		++i;
	}
	while (is_space(string, i))
		i++;
	if (string[i] == '\0' || string[i] == '<' || string[i] == '|'
		|| string[i] == '>')
		return (false);
	return (redir_left_count <= 2);
}

bool	is_valid_redir_right(char *string, size_t remaining)
{
	size_t	i;
	size_t	redir_left_count;

	i = 1;
	redir_left_count = 1;
	while (i < remaining && string[i] == '>')
	{
		redir_left_count += 1;
		++i;
	}
	while (is_space(string, i))
		i++;
	if (string[i] == '\0' || string[i] == '<' || string[i] == '|'
		|| string[i] == '>')
		return (false);
	return (redir_left_count <= 2);
}

bool	is_valid_pipe(char *string)
{
	size_t	i;

	i = 1;
	while (is_space(string, i))
		i++;
	if (string[i] == '|' || string[i] == '\0')
		return (false);
	return (true);
}

bool	is_valid_operator(char *str, size_t remain, t_operator_kind kind)
{
	if (kind == kind_pipe)
		return (is_valid_pipe(str));
	else if (kind == kind_redir_right)
		return (is_valid_redir_right(str, remain));
	else if (kind == kind_redir_left)
		return (is_valid_redir_left(str, remain));
	return (true);
}

bool	is_operator(char ch, t_operator_kind *out_kind)
{
	if (ch == '|')
	{
		*out_kind = kind_pipe;
		return (true);
	}
	else if (ch == '>')
	{
		*out_kind = kind_redir_right;
		return (true);
	}
	else if (ch == '<')
	{
		*out_kind = kind_redir_left;
		return (true);
	}
	return (false);
}
