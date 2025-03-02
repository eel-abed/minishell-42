/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:22:03 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/28 20:03:46 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c, t_garbage **gc)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**str;

	str = (char **)gc_malloc(gc, sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!s || !str)
		return (NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = i;
			while (s[i] != c && s[i])
				i++;
			str[k] = ft_substr(s, j, i - j, gc);
			k++;
		}
		else
			i++;
	}
	str[k] = NULL;
	return (str);
}
