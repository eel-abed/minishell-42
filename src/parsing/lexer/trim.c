/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:21 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/04 18:50:37 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_matching_quote(char c, char quote_type)
{
	return (c == quote_type);
}

static void	handle_quote_removal(char *str, int *i, int *j, char *result)
{
	static char	quote;

	if ((str[*i] == '"' || str[*i] == '\''))
	{
		if (!quote)
		{
			quote = str[*i];
			(*i)++;
		}
		else if (is_matching_quote(str[*i], quote))
		{
			quote = 0;
			(*i)++;
		}
		else
		{
			result[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
		return ;
	}
	result[*j] = str[*i];
	(*i)++;
	(*j)++;
}

char	*remove_outer_quotes(char *str, t_garbage **gc)
{
	char	*result;
	int		i;
	int		j;

	if (!str || !str[0])
		return (ft_strdup(str, gc));
	if (!(result = gc_malloc(gc, ft_strlen(str) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
		handle_quote_removal(str, &i, &j, result);
	result[j] = '\0';
	return (result);
}

// char	*remove_outer_quotes(char *str, t_garbage **gc)
// {
// 	char	*result;
// 	int		i;
// 	int		j;
// 	char	current_quote;

// 	if (!str || !str[0])
// 		return (ft_strdup(str, gc));
// 	if (!(result = gc_malloc(gc, ft_strlen(str) + 1)))
//         return (NULL);
// 	i = 0;
// 	j = 0;
// 	current_quote = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] == '"' || str[i] == '\''))
// 		{
// 			if (!current_quote)
// 				current_quote = str[i++];
// 			else if (is_matching_quote(str[i], current_quote))
// 			{
// 				current_quote = 0;
// 				i++;
// 			}
// 			else
// 				result[j++] = str[i++];
// 		}
// 		else
// 			result[j++] = str[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

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

char	*get_clean_word(char *str, t_garbage **gc)
{
	char	*result;
	int		i;
	int		j;

	result = gc_malloc(gc, ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
