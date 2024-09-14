/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:58:02 by mafourni          #+#    #+#             */
/*   Updated: 2024/07/19 18:16:08 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	ft_lstclear(t_list **lst, void (*del)(void(*)))
// {
// 	t_list	*tmp;

// 	while ((*lst) != NULL)
// 	{
// 		del((*lst)->content);
// 		tmp = (*lst);
// 		(*lst) = (*lst)->next;
// 		if (tmp != NULL)
// 			free(tmp);
// 	}
// }
