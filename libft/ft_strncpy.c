/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 01:58:18 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/14 01:17:33 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
        // printf("dest = [%c], index [%d]\n",dest[i],i);
		i++;
	}
    // printf("DEBUG 1\n");
	// while (i < n)
	// {
	dest[i] = '\0';
	// 	i ++;
	// }
    // printf("DEBUG 2\n");
    // printf("dest = [%s]",dest);
	return (dest);
}