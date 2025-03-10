/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:15:42 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 19:15:18 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	has_empty_quotes_at_start(char *str)
{
	return (str[0] == str[1] && (str[0] == '"' || str[0] == '\''));
}

int	is_export_cmd(char *str, t_garbage **gc)
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
	result = !ft_strcmp(clean_str, "export");
	return (result);
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
