/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:39:16 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/22 11:21:02 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_;
	unsigned char		c_;
	unsigned int		i;

	i = 0;
	s_ = (const unsigned char *) s;
	c_ = (const unsigned char) c;
	if (!s)
		return (0);
	while (i < n)
	{
		if (c_ == s_[i])
			return ((void *)(s_ + i));
		i++;
	}
	return (0);
}
