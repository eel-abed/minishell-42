/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:35:39 by mafourni          #+#    #+#             */
/*   Updated: 2024/07/19 18:16:17 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_lst;
// 	t_list	*new_obj;

// 	if (lst == NULL)
// 		return (NULL);
// 	new_lst = NULL;
// 	while (lst != NULL)
// 	{
// 		new_obj = ft_lstnew(f(lst->content));
// 		if (!new_obj)
// 			return (ft_lstclear(&new_lst, del), NULL);
// 		ft_lstadd_back(&new_lst, new_obj);
// 		lst = lst->next;
// 	}
// 	return (new_lst);
// }
