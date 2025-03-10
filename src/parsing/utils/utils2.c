/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:11:55 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 18:41:15 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*ft_strcpy(char *dest, t_might replace_mr, int i, t_garbage **gc)
{
	int	index;
	int	len;

	index = 0;
	len = i - replace_mr.j;
	dest = gc_malloc(gc, sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (index < len)
	{
		dest[index] = replace_mr.input[replace_mr.j];
		replace_mr.j++;
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

int	detect_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
