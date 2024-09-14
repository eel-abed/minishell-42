/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexmaj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:17:55 by mafourni          #+#    #+#             */
/*   Updated: 2024/03/05 16:23:54 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putnbr(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb > 9)
	{
		len += ft_putnbr(nb / 10);
	}
	len += ft_putchar(nb % 10 + '0');
	return (len);
}

static int	ft_writehex(unsigned int n)
{
	int	len;

	len = 0;
	if (n % 16 == 10)
		len += write(1, "A", 1);
	else if (n % 16 == 11)
		len += write(1, "B", 1);
	else if (n % 16 == 12)
		len += write(1, "C", 1);
	else if (n % 16 == 13)
		len += write(1, "D", 1);
	else if (n % 16 == 14)
		len += write(1, "E", 1);
	else if (n % 16 == 15)
		len += write(1, "F", 1);
	else
		len += ft_putnbr(n % 16);
	return (len);
}

static int	ft_putnbrhex(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 15)
		len += ft_putnbrhex(n / 16);
	len += ft_writehex(n);
	return (len);
}

int	print_hexmaj(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
		len += ft_putnbrhex(n);
	return (len);
}
