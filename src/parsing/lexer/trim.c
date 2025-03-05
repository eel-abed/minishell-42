/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:21 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/05 16:25:22 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	handle_quote_char(t_quote_params *params)
{
	if (!params->quote)
	{
		params->quote = params->str[*params->i];
		(*params->i)++;
	}
	else if (is_matching_quote(params->str[*params->i], params->quote))
	{
		params->quote = 0;
		(*params->i)++;
	}
	else
	{
		params->result[*params->j] = params->str[*params->i];
		(*params->i)++;
		(*params->j)++;
	}
}

char	*remove_outer_quotes(char *str, t_garbage **gc)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	if (!str || !str[0])
		return (ft_strdup(str, gc));
	if (!(result = gc_malloc(gc, ft_strlen(str) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\''))
			handle_quote_char(&(t_quote_params){str, &i, &j, quote, result});
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
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
