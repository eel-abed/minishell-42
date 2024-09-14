/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:22:49 by mafourni          #+#    #+#             */
/*   Updated: 2024/06/18 14:12:36 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*b_;
	unsigned char	c_;

	b_ = (unsigned char *) b;
	c_ = (unsigned char) c;
	if (!b)
		return (0);
	while (len--)
	{
		*b_++ = c_;
	}
	return (b);
}
