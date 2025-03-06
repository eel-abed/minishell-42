/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:57:33 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 19:47:32 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_if_loop(int *x, int *y, t_tokens *current, int i)
{
	if (current->value[i] == '"' && *y == 0)
		*y = 1;
	if (current->value[i] == '\'' && *y == 0)
		*y = 2;
	if ((*y == 1 && current->value[i] == '"') || (*y == 2
			&& current->value[i] == '\''))
		*x += 1;
}

// void	ft_error_export_clean_loop(t_tokens *current, int i, char *trimmed,
// 		char *clen_trimmed, t_garbage **gc)
// {
// 	clen_trimmed = ft_strjoin(ft_substr(current->value, 0, i, gc), trimmed, gc);
// 	current->value = clen_trimmed;
// }

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

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}
