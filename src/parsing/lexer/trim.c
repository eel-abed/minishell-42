/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:21 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/18 19:46:36 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*remove_outer_quotes(char *str)
{
	char	*result;
	char	outer_quote;
	int		i;
	int		j;

	if (!str || !str[0])
		return (ft_strdup(str));
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	if (has_empty_quotes_at_start(str))
		i += 2;
	while (str[i] && !is_quote(str[i]))
		result[j++] = str[i++];
	if (str[i])
		outer_quote = str[i++];
	else
		outer_quote = 0;
	while (str[i])
	{
		if (str[i] == outer_quote && str[i + 1] == outer_quote)
			i += 2;
		else if (str[i] == outer_quote && str[i + 1] == 0)
			i++;
		else
			result[j++] = str[i++];
	}
	return (result[j] = '\0', result);
}

int	should_trim_quotes(char *str)
{
	int	len;
	int	i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len == 2 && ((str[0] == '"' && str[1] == '"') || (str[0] == '\''
				&& str[1] == '\'')))
		return (0);
	if (len >= 2 && ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\''
				&& str[len - 1] == '\'')))
	{
		i = 1;
		while (i < len - 1)
		{
			if (str[i] != ' ' && str[i] != '\t')
				return (1);
			i++;
		}
		return (0);
	}
	return (0);
}

int	has_attached_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && ((i > 0 && str[i - 1] != ' ')
				|| (str[i + 1] && str[i + 1] != ' ')))
			return (1);
		i++;
	}
	return (0);
}

t_tokens	*ft_trim_all(t_tokens *tokens)
{
	t_tokens	*current;
	char		*trimmed;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current)
	{
		if (current->value)
		{
			if (has_attached_quotes(current->value)
				|| should_trim_quotes(current->value))
			{
				trimmed = remove_outer_quotes(current->value);
				free(current->value);
				current->value = trimmed;
			}
		}
		current = current->next;
	}
	return (tokens);
}
