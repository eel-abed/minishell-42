/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:25:13 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 17:17:45 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

int	is_echo_cmd(char *str, t_garbage **gc)
{
	char	*outer_quotes_removed;
	char	*clean_str;
	int		result;

	if (!str)
		return (0);
	outer_quotes_removed = remove_outer_quotes(str, gc);
	if (!outer_quotes_removed)
		return (0);
	clean_str = get_clean_word(outer_quotes_removed, gc);
	if (!clean_str)
		return (0);
	result = !ft_strcmp(clean_str, "echo");
	return (result);
}

t_tokens	*ft_trim_all(t_tokens *tokens, t_garbage **gc)
{
	t_tokens	*current;
	char		*trimmed;
	int			in_export;

	if (!tokens)
		return (NULL);
	current = tokens;
	in_export = 0;
	while (current)
	{
		if (current->value)
		{
			if (is_export_cmd(current->value, gc))
			{
				trimmed = get_clean_word(current->value, gc);
				current->value = trimmed;
				in_export = 1;
			}
			else if (current->type == kind_pipe)
				in_export = 0;
			else if (in_export)
				ft_trim_export(current, gc);
			else if (!in_export && (has_attached_quotes(current->value)
					|| should_trim_quotes(current->value)) /*
				&& current->type == kind_none*/)
			{
				trimmed = remove_outer_quotes(current->value, gc);
				current->value = trimmed;
			}
		}
		current = current->next;
	}
	return (tokens);
}

int	is_matching_quote(char c, char quote_type)
{
	return (c == quote_type);
}
