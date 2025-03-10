/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_listfunctions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 02:02:14 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/05 16:19:09 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	mini_lstadd_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
		return ;
	}
	tmp = *lst;
	while ((tmp)->next != NULL)
		(tmp) = (tmp)->next;
	(tmp)->next = new;
	new->next = NULL;
	new->prev = tmp;
}

void	mini_lstadd_front(t_tokens **lst, t_tokens *new)
{
	new->next = *lst;
	*lst = new;
}

t_tokens	*mini_lstlast(t_tokens *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_tokens	*mini_lstnew(char *value, int kind, t_garbage **gc)
{
	t_tokens	*newlst;

	newlst = gc_malloc(gc, sizeof(t_tokens));
	if (!newlst)
		return (NULL);
	newlst->prev = NULL;
	newlst->type = kind;
	newlst->value = value;
	newlst->next = NULL;
	return (newlst);
}

int	mini_lstsize(t_tokens *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
