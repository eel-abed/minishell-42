/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:57:33 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/04 18:34:25 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_error_export_clean_loop(t_tokens *current, int i, char *trimmed,
		char *clen_trimmed, t_garbage **gc)
{
	clen_trimmed = ft_strjoin(ft_substr(current->value, 0, i, gc), trimmed, gc);
	current->value = clen_trimmed;
}

static char	*removing(char *value, t_garbage **gc)
{
	int		i;
	char	current_quote;
	char	*before;
	char	*after;
	char	*tmp;

	if ((value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		|| (value[0] == '"' && value[ft_strlen(value) - 1] == '"'))
		value = ft_substr(value, 1, ft_strlen(value) - 2, gc);
	i = 0;
	current_quote = 0;
	while (value && value[i])
	{
		if (value[i] == '"' && current_quote == 0)
		{
			before = ft_substr(value, 0, i, gc);
			after = ft_substr(value, i + 1, ft_strlen(value) - i - 1, gc);
			tmp = ft_strjoin(before, after, gc);
			value = tmp;
			i--;
		}
		i++;
	}
	return (value);
}

void	ft_clean_words_export(t_tokens *current, t_garbage **gc)
{
	char	*equals;
	char	*key;
	char	*value;

	equals = ft_strchr(current->value, '=');
	if (!equals)
		return ;
	key = ft_substr(current->value, 0, equals - current->value + 1, gc);
	value = ft_strdup(equals + 1, gc);
	value = removing(value, gc);
	current->value = ft_strjoin(key, value, gc);
}

void	ft_export_clean_and(t_tokens *current, char *trimmed, char *tem,
		t_garbage **gc)
{
	if (current->value[0] == '\'')
	{
		tem = ft_substr(current->value, 1, ft_strlen(current->value) - 1, gc);
		current->value = tem;
	}
	if (current->value[0] != '"')
	{
		trimmed = ft_strjoin("\"", current->value, gc);
		current->value = trimmed;
	}
	if (current->value[ft_strlen(current->value) - 1] == '\'')
	{
		tem = ft_substr(current->value, 0, ft_strlen(current->value) - 1, gc);
		current->value = tem;
	}
	if (current->value[ft_strlen(current->value) - 1] != '"')
	{
		trimmed = ft_strjoin(current->value, "\"", gc);
		current->value = trimmed;
	}
}

void	ft_trim_export(t_tokens *tokens, t_garbage **gc)
{
	t_tokens	*current;
	char		*trimmed;
	char		*tem;
	int			i;
	int			y;

	i = 0;
	y = 0;
	if (!tokens)
		return ;
	current = tokens;
	ft_clean_words_export(current, gc);
	while (current->value[i] && current->value[i + 1])
	{
		if (current->value[i] == '=' && y == 0)
			y = 1;
		if (current->value[i] == '\'' && current->value[i + 1] == '\''
			&& y == 1)
		{
			tem = ft_substr(current->value, 0, i + 1, gc);
			trimmed = ft_substr(current->value, i + 2, ft_strlen(current->value)
					- i, gc);
			current->value = ft_strjoin(tem, trimmed, gc);
		}
		i++;
	}
	ft_export_clean_and(current, trimmed, tem, gc);
}
