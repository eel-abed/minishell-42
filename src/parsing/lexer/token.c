/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:28:42 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 13:02:38 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	should_preserve_token(t_tokens *token)
{
	if (!token || !token->prev)
		return (1);
	if (token->prev->type != kind_none)
		return (1);
	return (0);
}

void	remove_empty_head(t_tokens **list)
{
	t_tokens	*current;

	if (should_preserve_token(*list))
		return ;
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

void	remove_outer_quotes_from_tokens(t_tokens **list, t_garbage **gc)
{
    t_tokens	*current;

    remove_empty_head(list);
    if (!*list)
        return ;
    current = *list;
    while (current)
    {
        if (is_empty_or_quoted_empty(current->value))
        {
            current->value = remove_outer_quotes(current->value, gc);
        }
        current = current->next;
    }
}

t_tokens	*ft_tokenizer_cmd_or_ope(char **split_result, t_garbage **gc)
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
		mini_lstadd_back(&token_list, mini_lstnew(split_result[i], type, gc));
	}
	return (token_list);
}

t_tokens	*lets_tokeninze(char *input, t_garbage **gc)
{
	t_tokens	*token_list;
	char		**split_result;
	int			i;

	token_list = NULL;
	split_result = split_mini(input, gc);
	i = 0;
	while (split_result[i])
		i++;
	token_list = ft_tokenizer_cmd_or_ope(split_result, gc);
	remove_outer_quotes_from_tokens(&token_list,gc);
	return (token_list);
}
