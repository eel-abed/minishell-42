/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:57:33 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/02 17:01:28 by mafourni         ###   ########.fr       */
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

void	ft_error_export_clean_loop(t_tokens *current, int i, char *trimmed,
		char *clen_trimmed, t_garbage **gc)
{
	clen_trimmed = ft_strjoin(ft_substr(current->value, 0, i, gc), trimmed, gc);
	current->value = clen_trimmed;
}

// void ft_clean_words_export(t_tokens *current,t_garbage **gc)
// {
//     int i = 0;
//     char *after_str;
//     char *result;
    
//     result = NULL;
//     after_str = NULL;
//     while (current->value[i])
//     {
//         if ((current->value[i] == '"') || (current->value[i] == '\''))
//         {
//             after_str = ft_substr(current->value, i + 1, ft_strlen(current->value) - 1, gc);
//             result = ft_strjoin(ft_substr(current->value, 0, i,gc), after_str, gc);
//             free(current->value);
//             free(after_str);
//             current->value = result;
//             i = -1;
//         }
//         i++;
//     }
// }

// void ft_clean_words_export(t_tokens *current, t_garbage **gc)
// {
//     int     i;
//     char    *key;
//     char    *value;
//     char    *equals;
//     char    *result;
//     char    current_quote;

//     equals = ft_strchr(current->value, '=');
//     if (!equals)
//         return;
//     key = ft_substr(current->value, 0, equals - current->value + 1, gc);
//     value = ft_strdup(equals + 1, gc);
//     if ((value[0] == '\'' && value[ft_strlen(value) - 1] == '\'') ||
//         (value[0] == '"' && value[ft_strlen(value) - 1] == '"'))
//     {
//         char *tmp = ft_substr(value, 1, ft_strlen(value) - 2, gc);
//         value = tmp;
//     }
//     i = 0;
//     current_quote = 0;
//     while (value && value[i])
//     {
//         if (value[i] == '"' && current_quote == 0)
//         {
//             char *before = ft_substr(value, 0, i, gc);
//             char *after = ft_substr(value, i + 1, ft_strlen(value) - i - 1, gc);
//             char *tmp = ft_strjoin(before, after, gc);
//             value = tmp;
//             i--;
//         }
//         i++;
//     }
//     result = ft_strjoin(key, value, gc);
//     current->value = result;
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

void ft_export_clean_and(t_tokens *current, char *trimmed, char *tem,t_garbage **gc)
{
    if (current->value[0] == '\'')
    {
        tem = ft_substr(current->value, 1, ft_strlen(current->value) - 1,gc);
        current->value = tem;	
    }
    if (current->value[0] != '"')
    {
        trimmed = ft_strjoin("\"", current->value,gc);
        current->value = trimmed;
    }
    if (current->value[ft_strlen(current->value) - 1] == '\'')
    {
        tem = ft_substr(current->value, 0, ft_strlen(current->value) - 1,gc);
        current->value = tem;
    }
    if (current->value[ft_strlen(current->value) - 1] != '"')
    {
        trimmed = ft_strjoin(current->value, "\"",gc);
        current->value = trimmed;
	}
}

// void ft_clean(t_tokens *current, int i,t_garbage **gc)
// {
//     char *before_s;
//     char *adfter_s; 
//     char *join_before;
//     char *result;

//     before_s = ft_substr(current->value, 0, i + 1,gc);
//     adfter_s = ft_substr(current->value, i + 1, ft_strlen(current->value) - i,gc);
//     join_before = ft_strjoin(before_s, "\"",gc);
//     result = ft_strjoin(join_before, adfter_s,gc);
//     current->value = result;
// }

// void ft_clean2(t_tokens *current, int i, t_garbage **gc)
// {
//     char *before_s;
//     char *adfter_s; 
//     char *join_before;
//     char *result;

//     before_s = ft_substr(current->value, 0, i + 1,gc);
//     adfter_s = ft_substr(current->value, i + 1, ft_strlen(current->value) - i,gc);
//     join_before = ft_strjoin(before_s, "\"",gc);
//     result = ft_strjoin(join_before, adfter_s,gc);
//     current->value = result;
// }

// void ft_clean_wd(t_tokens *current, int y, int i,t_garbage **gc)
// {
//     int find_equal;
//     int x;

//     find_equal = 0;
//     x = 0;
//     while (current->value[i])
//     {
//         if ((current->value[i] == '"' || (current->value[i] == '=' && current->value[i + 1] && current->value[i + 1 ] != '"')) && y == 0)
//             y = 1;
//         if ((y == 1 && current->value[i] == '"') || (y == 2 && current->value[i] == '\'') )
//             x++;
//         if ((current->value[i] == '=' && current->value[i+1] && current->value[i+1] != '"') &&  (x == 1 || x == 0) && find_equal == 0)
//         {
//             ft_clean(current, i,gc);
//             y = 1;
//             i++;
//             find_equal = 1;
//         }
//         else if (find_equal == 1 && current->value[i] == '"') 
//         {
//             ft_clean2(current, i,gc);
//             y = 1;
//             x++;
//             find_equal = 0;
//         }
//         i++;
//     }
// }

void ft_trim_export(t_tokens *tokens,t_garbage **gc)
{
    t_tokens		*current;
	char			*trimmed;
    char				*tem;
	int					i;
	int					y;

    i = 0;
    y = 0;
	if (!tokens)
		return ;
	current = tokens;
    ft_clean_words_export(current,gc);
    while (current->value[i] && current->value[i + 1])
    {
        if (current->value[i] == '=' && y == 0)
            y = 1;
        if (current->value[i] == '\'' && current->value[i + 1] == '\'' && y == 1)
        {
            tem = ft_substr(current->value, 0, i + 1,gc);
            trimmed = ft_substr(current->value, i + 2, ft_strlen(current->value) - i,gc);
            current->value = ft_strjoin(tem, trimmed,gc);
        }
        i++;
    }
    ft_export_clean_and(current, trimmed, tem,gc);
    // i = 0;
    // y = 0;
    // ft_clean_wd(current, y, i,gc);
}
