/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:22:02 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/25 18:01:57 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int content)
{
	t_list	*newlst;

	newlst = malloc(sizeof (t_list));
	if (!newlst)
		return (NULL);
	newlst->index = -1;
	newlst->flag = -1;
	newlst->content = content;
	newlst->next = NULL;
	return (newlst);
}

