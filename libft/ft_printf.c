/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:49:16 by maxencefour       #+#    #+#             */
/*   Updated: 2024/03/05 17:24:35 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	len;
	size_t	i;

	if (!format)
		return (-1);
	va_start(ap, format);
	len = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
			len += print_format(format[++i], ap);
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}
// int	main(void)
// {
// int yo;
// int ya;
// ya = 0;
// yo = 0;
// char *str;
// str = NULL;
// ya = printf(str, -7897895);
// printf("Le nb de caracteres ecris est %d\n", ya);
// yo = ft_printf(str, -7897895);
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// // 	printf("\n\n");
// 	ya = printf("X = %X\n", -7897895);
// 	printf("Le nb de caracteres ecris est %d\n", ya);
// 	yo = ft_printf("X = %X\n", -7897895);
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// 	printf("\n\n");
// ya = printf("P =%p\n", &str);
// printf("Le nb de caracteres ecris est %d\n", ya);
// printf("Le nb de caracteres ecris est %d\n", yo);
// 	printf("\n\n");
// 	ya = printf("C =%c\n", 'c');
// 	printf("Le nb de caracteres ecris est %d\n", ya);
// 	yo = ft_printf("C =%c\n", 'c');
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// 	printf("\n\n");
// 	ya = printf("S=%s\n", str);
// 	printf("Le nb de caracteres ecris est %d\n", ya);
// 	yo = ft_printf("S=%s\n", str);
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// 	printf("\n");
// 	ya = printf("I = %i\n", 125);
// 	printf("Le nb de caracteres ecris est %d\n", ya);
// 	yo = ft_printf("I = %i\n", 125);
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// 	printf("\n");
// 	ya = printf("D = %d\n", -123);
// 	printf("Le nb de caracteres ecris est %d\n", ya);
// 	yo = ft_printf("D = %d\n", -123);
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// 	ya = printf("u = %u\n", 2147483647);
// 	printf("Le nb de caracteres ecris est %d\n", ya);
// 	yo = ft_printf("u = %u\n", 2147483647);
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// 	ya = printf("percent = %%\n");
// 	printf("Le nb de caracteres ecris est %d\n", ya);
// 	yo = ft_printf("percent = %%\n");
// 	printf("Le nb de caracteres ecris est %d\n", yo);
// 	return (0);
// }