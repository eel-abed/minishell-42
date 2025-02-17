/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:28:42 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/17 19:25:44 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int check_empty_quotes(char *str, int len)
{
    // Check for empty quotes ("" or '')
    if (len == 2 && ((str[0] == '"' && str[1] == '"') || 
        (str[0] == '\'' && str[1] == '\'')))
        return (1);
        
    // Check for quotes with only spaces
    if ((str[0] == '"' && str[len - 1] == '"') || 
        (str[0] == '\'' && str[len - 1] == '\''))
    {
        int i = 1;
        while (i < len - 1)
        {
            if (str[i] != ' ' && str[i] != '\t')
                return (0);
            i++;
        }
        return (1);
    }
    return (-1);
}

static int is_empty_or_quoted_empty(char *str)
{
    int i;
    int len;
    int quoted_result;

    if (!str || !str[0])
        return (1);
    len = ft_strlen(str);
    if (len < 2)
        return (0);
    quoted_result = check_empty_quotes(str, len);
    if (quoted_result != -1)
        return (quoted_result);
    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}
static int should_preserve_token(t_tokens *token)
{
    if (!token || !token->prev)
        return (1);  // Preserve first token
    if (token->prev->type != kind_none)
        return (1);  // Preserve tokens after operators
    return (0);
}

static void remove_empty_head(t_tokens **list)
{
    t_tokens *current;

    if (should_preserve_token(*list))
        return;
    while (*list && is_empty_or_quoted_empty((*list)->value))
    {
        current = *list;
        *list = (*list)->next;
        if (*list)
            (*list)->prev = NULL;
        free(current->value);
        free(current);
    }
}

void remove_empty_tokens(t_tokens **list)
{
    t_tokens *current;
    t_tokens *next;

    remove_empty_head(list);
    if (!*list)
        return;
    current = *list;
    while (current && current->next)
    {
        next = current->next;
        if (is_empty_or_quoted_empty(next->value) && !should_preserve_token(next))
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

t_tokens	*ft_tokenizer_cmd_or_ope(char **split_result)
{
	t_tokens		*token_list;
	t_operator_kind	type;
	int				i;

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
t_tokens	*lets_tokeninze(char *input)
{
	t_tokens	*token_list;
	char		**split_result;
	// int			i;

	// i = 0;
	token_list = NULL;
	split_result = split_mini(input);
	// while (split_result[i])
	// {
	//     printf("Split[%d] = [%s]\n", i, split_result[i]);
	//     i++;
	// }
	// if (split_result[i] == NULL)
	//     printf("Split[%d] = [%s]\n", i, split_result[i]);
	token_list = ft_tokenizer_cmd_or_ope(split_result);
    printf("BEFORE REMOVE EMPTY TOKENS\n");
	print_tokens(token_list);
	remove_empty_tokens(&token_list);
    printf("AFTER REMOVE EMPTY TOKENS\n");
	print_tokens(token_list);
	return (token_list);
}