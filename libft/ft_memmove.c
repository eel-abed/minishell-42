/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:26:08 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/22 14:54:35 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*char_dst;
	unsigned char	*char_src;

	char_dst = (unsigned char *) dst;
	char_src = (unsigned char *) src;
	if (!dst || !src)
		return (0);
	if (char_dst <= char_src)
	{
		while (len--)
		{
			*char_dst++ = *char_src++;
		}
	}
	else
	{
		while (len--)
		{
			char_dst[len] = char_src[len];
		}
	}
	return (dst);
}
