/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:29:01 by mafourni          #+#    #+#             */
/*   Updated: 2024/06/18 14:12:06 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		len++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*copie;
	int		len;
	long	nb;

	nb = n;
	len = ft_len(nb);
	copie = malloc(sizeof(char) * (len + 1));
	if (!copie)
		return (NULL);
	if (nb == 0)
		copie[0] = '0';
	if (n < 0)
	{
		copie[0] = '-';
		nb = -nb;
	}
	copie[len--] = '\0';
	while (nb != 0)
	{
		copie[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (copie);
}
