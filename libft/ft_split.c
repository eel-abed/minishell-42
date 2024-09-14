/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:01:17 by mafourni          #+#    #+#             */
/*   Updated: 2024/07/10 16:20:12 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (s[i +1] == c || s[i +1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	ft_malloc_well(char **oe, size_t position, size_t len)
{
	size_t	i;

	oe[position] = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!oe[position])
	{
		while (i < position)
			free (oe[i++]);
		free (oe);
		return (1);
	}
	return (0);
}

int	ft_fullfill(char	**ptr, char const *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (ft_malloc_well(ptr, i, len))
				return (1);
			ft_strlcpy(ptr[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	nbarrays;
	char	**ptr;

	if (!s)
		return (NULL);
	nbarrays = ft_countwords(s, c);
	ptr = malloc(sizeof(char *) * (nbarrays + 1));
	if (!ptr)
		return (NULL);
	if (ft_fullfill(ptr, s, c))
		return (NULL);
	ptr[nbarrays] = NULL;
	return (ptr);
}
