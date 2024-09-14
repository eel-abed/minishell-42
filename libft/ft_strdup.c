/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:32:31 by mafourni          #+#    #+#             */
/*   Updated: 2024/03/11 19:54:45 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// char	*ft_strdup(const char *s1)
// {
// 	int		len;
// 	int		i;
// 	char	*copie;

// 	if (!s1)
// 		return (0);
// 	len = 0;
// 	i = 0;
// 	while (s1[len])
// 		len++;
// 	copie = malloc(sizeof(char) * (len + 1));
// 	if (!copie)
// 		return (0);
// 	while (i < len)
// 	{
// 		copie[i] = s1[i];
// 		i++;
// 	}
// 	copie[i] = '\0';
// 	return (copie);
// }
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*result;
	size_t		length;
	size_t		i;

	length = ft_strlen (s1);
	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
