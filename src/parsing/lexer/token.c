/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:28:42 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/14 08:56:32 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_empty_or_quoted_empty(char *str)
{
    int	i;
    int	len;

    if (!str || !str[0])
        return (1);
    len = ft_strlen(str);
    if (len < 2)
        return (0);
    if ((str[0] == '"' && str[len - 1] == '"') ||
        (str[0] == '\'' && str[len - 1] == '\''))
    {
        i = 1;
        while (i < len - 1)
        {
            if (str[i] != ' ' && str[i] != '\t')
                return (0);
            i++;
        }
        return (1);
    }
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

void	remove_empty_tokens(t_tokens **list)
{
    t_tokens	*current;
    t_tokens	*next;

    while (*list && is_empty_or_quoted_empty((*list)->value))
    {
        current = *list;
        *list = (*list)->next;
        if (*list)
            (*list)->prev = NULL;
        free(current->value);
        free(current);
    }
    if (!*list)
        return ;
    current = *list;
    while (current && current->next)
    {
        next = current->next;
        if (is_empty_or_quoted_empty(next->value))
        {
            current->next = next->next;
            if (next->next)
                next->next->prev = current;
            free(next->value);
            free(next);
        }
        else
            current = current->next;
    }
}

t_tokens *ft_tokenizer_cmd_or_ope(char **split_result)
{
    t_tokens *token_list;
    t_operator_kind type;
    int i;

    token_list = NULL;
    i = -1;
    while (split_result[++i])
    {
        if (ft_strcmp(split_result[i], "|") == 0)
            type = kind_pipe;
        else if (ft_strcmp(split_result[i], "<") == 0)
            type = kind_redir_left;
        else if (ft_strcmp(split_result[i], ">") == 0)
            type = kind_redir_right;
        else if (ft_strcmp(split_result[i], "<<") == 0)
            type = kind_redir_2left;
        else if (ft_strcmp(split_result[i], ">>") == 0)
            type = kind_redir_2right;
        else
            type = kind_none;
        mini_lstadd_back(&token_list, mini_lstnew(split_result[i], type));
    }
    return (token_list);
}
t_tokens *lets_tokeninze(char *input)
{
    int i = 0;
    t_tokens  *token_list;
    char **split_result;
    split_result = split_mini(input);
    while (split_result[i])
    {
        printf("Split[%d] = [%s]\n", i, split_result[i]);
        i++;
    }
    token_list = ft_tokenizer_cmd_or_ope(split_result);
    print_tokens(token_list);
    remove_empty_tokens(&token_list);
    print_tokens(token_list);
    return (token_list);
}


