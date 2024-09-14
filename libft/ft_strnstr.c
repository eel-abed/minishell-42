/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 23:13:07 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/22 14:32:00 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*haystack_;
	size_t	i;
	size_t	j;

	haystack_ = (char *) haystack;
	i = 0;
	if (haystack_ == needle)
		return (haystack_);
	if (needle[0] == '\0')
		return (haystack_);
	if (haystack_[0] == '\0' && needle[0] == '\0')
		return (haystack_);
	while (haystack_[i] != '\0')
	{
		j = 0;
		while (needle[j] == haystack_[i + j] && needle[j] != '\0')
			j++;
		if (needle[j] == '\0' && i + j <= len)
			return (haystack_ + i);
		i++;
	}
	return (NULL);
}
