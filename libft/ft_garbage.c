/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:52:45 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/22 18:04:56 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void *gc_malloc(t_garbage **gc, size_t size) 
{
    void *ptr;
    t_garbage *new;

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

void gc_free_all(t_garbage **gc)
{
    t_garbage *current;
    t_garbage *next;

    current = *gc;
    while (current)
    {
        next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    *gc = NULL;
}