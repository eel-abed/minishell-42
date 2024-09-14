/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:22:53 by mafourni          #+#    #+#             */
/*   Updated: 2024/03/05 16:21:27 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putnbr(unsigned long long nb)
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

static int	ft_writehex(unsigned long long n)
{
	int	len;

	len = 0;
	if (n % 16 == 10)
		len += write(1, "a", 1);
	else if (n % 16 == 11)
		len += write(1, "b", 1);
	else if (n % 16 == 12)
		len += write(1, "c", 1);
	else if (n % 16 == 13)
		len += write(1, "d", 1);
	else if (n % 16 == 14)
		len += write(1, "e", 1);
	else if (n % 16 == 15)
		len += write(1, "f", 1);
	else
		len += ft_putnbr(n % 16);
	return (len);
}

static int	ft_putnbrhex(unsigned long long n)
{
	int	len;

	len = 0;
	if (n > 15)
		len += ft_putnbrhex(n / 16);
	len += ft_writehex(n);
	return (len);
}

int	print_ptr(unsigned long long n)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		len += ft_putnbrhex(n);
	}
	return (len);
}
