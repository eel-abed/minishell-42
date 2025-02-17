/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:09:21 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/17 12:52:27 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *trim_unquoted(char *str)
{
    char    *result;
    int     i;
    int     j;
    int     in_quotes;
    char    quote_type;
    
    if (!str)
        return (NULL);
    result = malloc(ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    
    i = 0;
    j = 0;
    in_quotes = 0;
    quote_type = 0;
    
    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '\"') && !in_quotes)
        {
            quote_type = str[i];
            in_quotes = 1;
            i++;
        }
        else if (str[i] == quote_type && in_quotes)
        {
            in_quotes = 0;
            quote_type = 0;
            i++;
        }
        else
        {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    free(str);
    return (result);
}


t_tokens *ft_trim_all(t_tokens *tokens)
{
    t_tokens *current;
    int in_command;
    
    if (!tokens)
        return (NULL);
    
    current = tokens;
    in_command = 0;
    
    while (current)
    {
        if (current->value)
        {
            // Handle export command
            if (ft_strcmp(current->value, "export") == 0)
            {
                in_command = 1;
            }
            // Handle echo command
            else if (ft_strcmp(current->value, "echo") == 0)
            {
                in_command = 1;
            }
            // Handle redirection target
            else if (current->type == kind_redir_left || 
                     current->type == kind_redir_right ||
                     current->type == kind_redir_2left || 
                     current->type == kind_redir_2right)
            {
                if (current->next)
                {
                    current->next->value = trim_unquoted(current->next->value);
                }
            }
            // For non-export/echo commands or non-redirection tokens, trim quotes
            else if (!in_command)
            {
                current->value = trim_unquoted(current->value);
            }
            
            // Reset command flag at pipe
            if (current->type == kind_pipe)
                in_command = 0;
        }
        current = current->next;
    }
    return (tokens);
}