/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:14:56 by mafourni          #+#    #+#             */
/*   Updated: 2024/04/06 18:02:56 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_putstr(char *str);
int		print_format(char found, va_list ap);
int		print_str(char *str);
int		print_char(char c);
int		print_hexmin(unsigned int n);
int		print_ptr(unsigned long long n);
int		print_hexmaj(unsigned int n);
int		print_nbr(int n);
int		print_nbru(unsigned int n);

#endif