/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:21 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/23 21:57:21 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_matching_quote(char c, char quote_type)
{
	return (c == quote_type);
}
char *remove_outer_quotes(char *str)
{
    char *result;
    int i;
    int j;
    char current_quote;

    if (!str || !str[0])
        return (ft_strdup(str));
    result = malloc(ft_strlen(str) + 1);
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

char	*get_clean_word(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
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

int	is_export_cmd(char *str)
{
	char	*outer_quotes_removed;
	char	*clean_str;
	int		result;

	if (!str)
		return (0);
	outer_quotes_removed = remove_outer_quotes(str);
	if (!outer_quotes_removed)
		return (0);
	clean_str = get_clean_word(outer_quotes_removed);
	free(outer_quotes_removed);
	if (!clean_str)
		return (0);
	result = !ft_strcmp(clean_str, "export");
	free(clean_str);
	return (result);
}

t_tokens	*ft_trim_all(t_tokens *tokens)
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
			if (is_export_cmd(current->value))
			{
				trimmed = get_clean_word(current->value);
				free(current->value);
				current->value = trimmed;
				in_export = 1;
				printf("is export");
			}
			else if (current->type == kind_pipe)
				in_export = 0;
			else if (in_export)
			// else if (in_export && (has_attached_quotes(current->value)
			// 		|| should_trim_quotes(current->value)))
			{
				printf("diego furea del trim export ---> %s\n", current->value);
				ft_trim_export(current);
				
			}
			else if (!in_export && (has_attached_quotes(current->value)
					|| should_trim_quotes(current->value)))
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

// t_tokens	*ft_trim_all(t_tokens *tokens)
// {
// 	t_tokens	*current;
// 	char		*trimmed;
// 	int			in_export;

// 	if (!tokens)
// 		return (NULL);
// 	current = tokens;
// 	in_export = 0;
// 	while (current)
// 	{
// 		if (current->value)
// 		{
// 			if (is_export_cmd(current->value))
// 			{
// 				trimmed = get_clean_word(current->value);
// 				free(current->value);
// 				current->value = trimmed;
// 				in_export = 1;
// 			}
// 			else if (current->type == kind_pipe)
// 				in_export = 0;
// 			else if (in_export && (has_attached_quotes(current->value)
// 					|| should_trim_quotes(current->value)))
// 			{
// 				int i = 0;
// 				int x = 0;
// 				int y = 0;

// 				char* tem;
// 				tem = NULL;
				
// 				while (current->value[i] && current->value[i + 1])
// 				{
// 					if (current->value[i] == '"' && y == 0)
// 						y = 1;
// 					if (current->value[i] == '\'' && y == 0)
// 						y = 2;
// 					if ((y == 1 && current->value[i] == '"') || (y == 2 && current->value[i] == '\''))
// 						x++;
// 					if (x % 2 == 0  && y != 0)
// 					{
						
// 						trimmed = ft_substr(current->value, i + 2, ft_strlen(current->value) - i);
// 						y = 0;
// 						if (current->value[i+1] == '"' && y == 0)
// 							y = 1;
// 						if (current->value[i+1] == '\'' && y == 0)
// 							y = 2;
// 						x = 1;
// 						char *clen_trimmed = ft_strjoin(ft_substr(current->value, 0, i), trimmed);
// 						free(current->value);
// 						free(trimmed);
// 						current->value = clen_trimmed;
		
// 					}
// 					i++;
// 				}
// 				// printf("diego ---> %s\n", current->value);
// 				// ! "And a quote at the end y a quote at the start"
// 				if (current->value[0] == '\'')
// 				{
// 					tem = ft_substr(current->value, 1, ft_strlen(current->value) - 1);
// 					free(current->value);
// 					current->value = tem;	
// 				}
// 				if (current->value[ft_strlen(current->value) - 1] != '"')
// 				{
// 					tem = ft_substr(current->value, 0, ft_strlen(current->value) - 1);
// 					free(current->value);
// 					current->value = tem;	
// 				}				
// 				if (current->value[0] != '"')
// 				{
// 					trimmed = ft_strjoin("\"", current->value);
// 					free(current->value);
// 					current->value = trimmed;
// 				}
// 				if (current->value[ft_strlen(current->value) - 1] != '"')
// 				{
// 					trimmed = ft_strjoin(current->value, "\"");
// 					free(current->value);
// 					current->value = trimmed;
// 				}	
// 				// Todo add the quotes to the start and the end of the string
// 				i = 0;
// 				x = 0;
// 				y = 0;

// 				int find_equal = 0;
// 				printf("diego ---> todo:%s\n", current->value);
// 				while (current->value[i])
// 				{
// 					if (current->value[i] == '"' && y == 0)
// 						y = 1;
// 					if ((y == 1 && current->value[i] == '"') || (y == 2 && current->value[i] == '\''))
// 						x++;
// 					// Todo : add the quotes to after the =
// 					if (current->value[i] == '=' &&  x == 1 && find_equal == 0)
// 					{
// 						char *before_s = ft_substr(current->value, 0, i + 1);
// 						char *adfter_s = ft_substr(current->value, i + 1, ft_strlen(current->value) - i);
// 						char *join_before = ft_strjoin(before_s, "\"");
// 						char *result = ft_strjoin(join_before, adfter_s);
// 						free(before_s);
// 						free(adfter_s);
// 						free(join_before);
// 						free(current->value);
// 						current->value = result;
// 						x++;
// 						y = 1;
// 						printf("diego add new before  ---> %s\n", current->value);
// 						find_equal = 1;
// 						i++;
// 					}
// 					else if (find_equal == 1 && current->value[i] == '"') 
// 					{
// 						char *before_s = ft_substr(current->value, 0, i + 1);
// 						char *adfter_s = ft_substr(current->value, i + 1, ft_strlen(current->value) - i);
// 						char *join_before = ft_strjoin(before_s, "\"");
// 						char *result = ft_strjoin(join_before, adfter_s);
// 						free(before_s);
// 						free(adfter_s);
// 						free(join_before);
// 						free(current->value);
// 						current->value = result;
// 						x++;
// 						y = 1;
// 						printf("diego add new after  ---> %s\n", current->value);
// 						find_equal = 0;
						
// 					}
// 					// Todo : add the quotes to the end the =
// 					i++;
// 				}
// 			}
// 			else if (!in_export && (has_attached_quotes(current->value)
// 					|| should_trim_quotes(current->value)))
// 			{
// 				trimmed = remove_outer_quotes(current->value);
// 				free(current->value);
// 				current->value = trimmed;
// 			}
// 		}
// 		current = current->next;
// 	}
// 	return (tokens);
// }