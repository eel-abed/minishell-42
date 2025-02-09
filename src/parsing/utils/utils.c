/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:50:05 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/09 17:52:55 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int skip_space (char *input, int i)
{
	int j = i + 1;
	while(input[j] == 32 && input[j])
		j++;
	return(j);
}

bool is_space (char *input, int i)
{
    if (input[i] == 32)
        return true;
    return false;
}