/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:20:30 by mafourni          #+#    #+#             */
/*   Updated: 2024/02/22 11:48:28 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copie;

	copie = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!copie)
		return (0);
	ft_strlcpy(copie, s1, (ft_strlen(s1) + ft_strlen(s2)) + 1);
	ft_strlcat(copie, s2, (ft_strlen(s1) + ft_strlen(s2)) + 1);
	return (copie);
}
