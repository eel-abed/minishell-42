/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:25:10 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/28 20:03:40 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src, t_garbage **gc)
{
	int		leng;
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	leng = 0;
	while (src[leng] != '\0')
	{
		leng++;
	}
	dest = gc_malloc(gc, sizeof(char) * (leng + 1));
	if (dest == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
