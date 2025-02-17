/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:43 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/17 19:29:05 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char *build_cmd_str(t_tokens *cmd_start, t_tokens *current, t_tokens *tokens)
{
    char *cmd_str;
    char *tmp;

    cmd_str = ft_strdup("");
    while (cmd_start != current)
    {
        if (cmd_start != tokens)
        {
            tmp = cmd_str;
            cmd_str = ft_strjoin(cmd_str, " ");
            free(tmp);
        }
        tmp = cmd_str;
        cmd_str = ft_strjoin(cmd_str, cmd_start->value);
        free(tmp);
        cmd_start = cmd_start->next;
    }
    return (cmd_str);
}

char *handle_last_token(char *cmd_str, t_tokens *cmd_start, 
    t_tokens *current, t_tokens *tokens)
{
    char *tmp;

    if (!current->next && current->type != kind_pipe)
    {
        if (cmd_start != tokens)
        {
            tmp = cmd_str;
            cmd_str = ft_strjoin(cmd_str, " ");
            free(tmp);
        }
        tmp = cmd_str;
        cmd_str = ft_strjoin(cmd_str, current->value);
        free(tmp);
    }
    return (cmd_str);
}

void add_pipe_token(t_tokens **result, t_tokens **cmd_start, 
    t_tokens *current)
{
    t_tokens *new_token;

    if (current->type == kind_pipe)
    {
        new_token = mini_lstnew(ft_strdup("|"), kind_pipe);
        mini_lstadd_back(result, new_token);
        *cmd_start = current->next;
    }
}

t_tokens *token_with_pipe(t_tokens *tokens)
{
    t_tokens *current;
    t_tokens *cmd_start;
    t_tokens *result;
    t_tokens *new_token;
    char    *cmd_str;

    if (!tokens)
        return (NULL);
    result = NULL;
    current = tokens;
    cmd_start = tokens;
    while (current)
    {
        if (current->type == kind_pipe || !current->next)
        {
            cmd_str = build_cmd_str(cmd_start, current, tokens);
            cmd_str = handle_last_token(cmd_str, cmd_start, current, tokens);
            new_token = mini_lstnew(cmd_str, kind_none);
            mini_lstadd_back(&result, new_token);
            add_pipe_token(&result, &cmd_start, current);
        }
        current = current->next;
    }
    return (result);
}