/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:01:46 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/05 16:19:28 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	quote_check(char *input, t_command *cmd)
{
	int		i;
	int		flag;
	char	to_found;

	i = 0;
	flag = -1;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			to_found = input[i];
			flag = 0;
			if_found(input, &i, &flag, to_found);
			i--;
		}
		i++;
	}
	if (flag != -1)
	{
		cmd->exit_status = 2;
		return (1);
	}
	else
		return (0);
}

void	if_found(char *input, int *i, int *flag, char to_found)
{
	(*i)++;
	while (input[*i] && *flag == 0)
	{
		if (input[*i] == to_found)
			*flag = -1;
		(*i)++;
	}
}
