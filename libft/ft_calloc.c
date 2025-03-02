/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:57:42 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/28 20:03:00 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size, t_garbage **gc)
{
	void	*ptr;

	ptr = gc_malloc(gc, count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	if (!ptr)
		return (NULL);
	return (ptr);
}
