/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:41:57 by mafourni          #+#    #+#             */
/*   Updated: 2024/06/18 14:12:16 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *str, size_t n)
{
	unsigned char		*destination;
	const unsigned char	*source;
	size_t				i;

	destination = dst;
	source = str;
	if (!destination && !source)
		return (NULL);
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}

// int main()
// {
// 	char *dst;
// 	dst = NULL;
// 	char *src;
// 	src = "ssw";
// 	printf("%s\n", ft_memcpy(dst, src, 0));
// 	printf("%s\n", memcpy(dst, src, 0));
// 	return (0);
// }
// void	*ft_memcpy(void *dest, const void *src, size_t n)
// {
// 	size_t	i;
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (i < n)
// 	{
// 		((char *)dest)[i] = ((char *)src)[i];
// 		i++;
// 	}
// 	return (dest);
// }

// int main()
// {
// 	char *dst;
// 	dst = "wsh";
// 	char *src;
// 	src = NULL;
// 	printf("%s\n", ft_memcpy(dst, src, 0));
// 	printf("%s\n", memcpy(dst, src, 0));
// 	return (0);
// }