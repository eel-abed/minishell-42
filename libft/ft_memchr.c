/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:17:57 by eel-abed          #+#    #+#             */
/*   Updated: 2023/10/28 16:36:07 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		chr;

	if (!s)
		return (NULL);
	ptr = s;
	chr = c;
	while (n--)
	{
		if (*ptr == chr)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
