/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:01:46 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/14 05:35:55 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	quote_check(char *input)
{
	int i;
	int flag;
	char to_found;

	i = 0;
	flag = -1;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			to_found = input[i];
			flag = 0;
			i++;
			while (input[i] && flag == 0)
			{
				if (input[i] == to_found)
					flag = -1;
				i++;
			}
			i--;
		}
		i++;
	}
	if (flag != -1)
		return (1);
	else
		return (0);
}