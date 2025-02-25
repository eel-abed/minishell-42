/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:57:42 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 18:21:11 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size,t_garbage **gc)
{
	void	*ptr;

	ptr = gc_malloc(gc,count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	if (!ptr)
		return (NULL);
	return (ptr);
}
