/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxencefournier <maxencefournier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2024/09/14 19:26:34 by maxencefour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
 
int main ()
{
	t_minis *mshl;
	while(1)
    {
		
		mshl->input = readline("MINISHEL : ");
		if (!mshl->input)
			return (write(1,"exit",4), 0);
	}
}


