/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:52:45 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/28 20:04:32 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gc_malloc(t_garbage **gc, size_t size)
{
	void		*ptr;
	t_garbage	*new;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new->ptr = ptr;
	new->next = *gc;
	*gc = new;
	return (ptr);
}

void	gc_free_all(t_garbage **gc)
{
	t_garbage	*current;
	t_garbage	*next;

	current = *gc;
	while (current)
	{
		next = current->next;
		if (current->ptr != NULL)
			free(current->ptr);
		if (current != NULL)
			free(current);
		current = next;
	}
	*gc = NULL;
}
