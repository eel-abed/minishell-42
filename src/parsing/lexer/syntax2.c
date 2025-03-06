/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:09:30 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 17:11:21 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	set_operator_kind(char ch, t_operator_kind *out_kind)
{
	if (ch == '|')
		*out_kind = kind_pipe;
	if (ch == '>')
		*out_kind = kind_redir_right;
	if (ch == '<')
		*out_kind = kind_redir_left;
}

bool	is_operator(char ch, t_operator_kind *out_kind)
{
	static char	quote = 0;

	if (ch == '"' || ch == '\'')
	{
		if (!quote)
			quote = ch;
		else if (ch == quote)
			quote = 0;
		return (false);
	}
	if (quote)
		return (false);
	if (ch == '|' || ch == '>' || ch == '<')
	{
		set_operator_kind(ch, out_kind);
		return (true);
	}
	return (false);
}
