/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:43:22 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/28 20:02:45 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n, t_garbage **gc)
{
	char	*str;
	int		len;
	long	nbr;

	nbr = n;
	len = ft_nbrlen(n);
	str = (char *)gc_malloc(gc, sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	while (--len >= 0 && nbr >= 10)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	str[len] = nbr + '0';
	return (str);
}
