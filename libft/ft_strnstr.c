/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:04:36 by eel-abed          #+#    #+#             */
/*   Updated: 2023/10/28 16:37:51 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	ptr = (char *)haystack;
	if (!*needle)
		return (ptr);
	while (ptr[i] && i < len)
	{
		j = 0;
		while (ptr[i + j] == needle[j] && i + j < len)
		{
			if (!needle[j + 1])
				return (&ptr[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
