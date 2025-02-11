/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:20:06 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/11 16:16:01 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}


// int main (int argc, char **argv)
// {
// 	int i = 0;
// 	printf("[%d]\n",ft_isalnum(argv[1][i]));
// 	printf("[%d]\n",ft_isalnum(argv[1][i+1]));

// 	// printf("Char  =%c ", argv[1][i]);
// 	while(argv[1][i] != '\0')
// 	{
// 		if(ft_isalnum(argv[1][i]))
// 		{
// 			printf("Char  =%c ", argv[1][i]);
// 			printf("Number or alpha\n");
// 		}
// 		printf("je i\n");
// 		i ++;
// 	}
// }