/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:38:26 by maxencefour       #+#    #+#             */
/*   Updated: 2024/03/05 16:21:41 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_format(char found, va_list ap)
{
	int	len;

	len = 0;
	if (found == 'c')
		len += print_char(va_arg(ap, int));
	else if (found == 's')
		len += print_str(va_arg(ap, char *));
	if (found == 'p')
		len += print_ptr(va_arg(ap, unsigned long long));
	else if (found == 'd' || found == 'i')
		len += print_nbr(va_arg(ap, int));
	else if (found == 'u')
		len += print_nbru(va_arg(ap, unsigned int));
	else if (found == 'x')
		len += print_hexmin(va_arg(ap, unsigned int));
	else if (found == 'X')
		len += print_hexmaj(va_arg(ap, unsigned int));
	else if (found == '%')
		len += write(1, "%%", 1);
	return (len);
}
