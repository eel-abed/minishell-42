/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:55 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/18 19:13:09 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strcpy(char *dest, char *src, int i, int j)
{
	int	index;
	int	len;

	index = 0;
	len = i - j;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (index < len)
	{
		dest[index] = src[j];
		j++;
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

int	detect_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
