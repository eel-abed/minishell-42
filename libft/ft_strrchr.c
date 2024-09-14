/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:01:57 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/22 21:41:34 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const unsigned char	*s_;
	unsigned char		c_;
	int					i;

	i = 0;
	c_ = (unsigned char) c;
	s_ = (const unsigned char *) s;
	if (!s)
		return (NULL);
	if (c_ == '\0')
	{
		while (s_[i] != '\0')
			i++;
		return ((char *)(s_ + i));
	}
	while (s_[i] != '\0')
		i++;
	while (--i > -1)
	{
		if (s_[i] == c_)
			return ((char *)(s_ + i));
	}
	return (0);
}
