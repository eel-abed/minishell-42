/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:42:52 by mafourni          #+#    #+#             */
/*   Updated: 2024/06/18 14:12:46 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = 0;
	len = ft_strlen(src);
	if (!src)
		return (0);
	i = 0;
	while (*src != '\0' && (i + 1 < dstsize))
	{
		*dst++ = *src++;
		i++;
	}
	if (dstsize > 0)
	{
		*dst = '\0';
	}
	return (len);
}
