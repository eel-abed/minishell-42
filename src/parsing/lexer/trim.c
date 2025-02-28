/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:21 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/28 19:54:30 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_matching_quote(char c, char quote_type)
{
	return (c == quote_type);
}
char *remove_outer_quotes(char *str,t_garbage **gc)
{
    char *result;
    int i;
    int j;
    char current_quote;

    if (!str || !str[0])
        return (ft_strdup(str,gc));
    result = gc_malloc(gc,ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    current_quote = 0;
    while (str[i])
    {
        if ((str[i] == '"' || str[i] == '\''))
        {
            if (!current_quote)
                current_quote = str[i++];
            else if (is_matching_quote(str[i], current_quote))
            {
                current_quote = 0;
                i++;
            }
            else
                result[j++] = str[i++];
        }
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

char	*get_clean_word(char *str,t_garbage **gc)
{
	char	*result;
	int		i;
	int		j;

	result = gc_malloc(gc,ft_strlen(str) + 1);
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

int	is_export_cmd(char *str,t_garbage **gc)
{
	char	*outer_quotes_removed;
	char	*clean_str;
	int		result;

	if (!str)
		return (0);
	outer_quotes_removed = remove_outer_quotes(str,gc);
	if (!outer_quotes_removed)
		return (0);
	clean_str = get_clean_word(outer_quotes_removed,gc);
	if (!clean_str)
		return (0);
	result = !ft_strcmp(clean_str, "export");
	return (result);
}

int	is_echo_cmd(char *str,t_garbage **gc)
{
	char	*outer_quotes_removed;
	char	*clean_str;
	int		result;

	if (!str)
		return (0);
	outer_quotes_removed = remove_outer_quotes(str,gc);
	if (!outer_quotes_removed)
		return (0);
	clean_str = get_clean_word(outer_quotes_removed,gc);
	if (!clean_str)
		return (0);
	result = !ft_strcmp(clean_str, "echo");
	return (result);
}

t_tokens	*ft_trim_all(t_tokens *tokens,t_garbage **gc)
{
	t_tokens	*current;
	size_t		i;
	char		*trimmed;
	int			in_export;
	int			is_echo;
	char		*before;
	char		*after;
	int closed;
	int y;

	if (!tokens)
		return (NULL);
	current = tokens;
	in_export = 0;
	is_echo = is_echo_cmd(current->value,gc);
	while (current)
	{
		if (current->value)
		{
			if (is_export_cmd(current->value,gc))
			{
				trimmed = get_clean_word(current->value,gc);
				current->value = trimmed;
				in_export = 1;
			}
			else if (current->type == kind_pipe)
				in_export = 0;
			else if (in_export)
				ft_trim_export(current,gc);	
			else if (is_echo == 1)
			{
				i = 1;
				closed = -1;
				y = 0;
				while (current->value[i])
				{
					if (current->value[i] == '\'' && y == 0 )
					{
						y = 1;
						closed = 0;
					}
					if (current->value[i] == '"' && y == 0 )
					{
						y = 2;
						closed = 0;
					}
					if (current->value[i] && y > 0 )
					{
						if ( 
							(closed == 0 && i < ft_strlen(current->value)  - 1 && ((y == 1 && current->value[i] == '\'') || (y == 2 && current->value[i] == '"')) ) 
							|| 
							(closed == 1 && ((y == 1 && current->value[i] == '\'') || (y == 2 && current->value[i] == '"')) )
						)
						{
							before = ft_substr(current->value, 0, i, gc);
							after = ft_substr(current->value, i + 1, ft_strlen(current->value) - i, gc);
							trimmed = ft_strjoin(before, after, gc);
							current->value = trimmed;
							if (closed == 0)
								closed = 1;
							else
							{
								closed = -1;
								y = 0;
							}
							i--;
						}
					}
					i++;
				}
			}			
			else if (!in_export && is_echo == 0 && (has_attached_quotes(current->value)
					|| should_trim_quotes(current->value)))
			{
				trimmed = remove_outer_quotes(current->value,gc);
				current->value = trimmed;
			}
		}
		current = current->next;
	}
	return (tokens);
}
