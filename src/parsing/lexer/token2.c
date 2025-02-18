/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:08:08 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/18 19:23:51 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_empty_quotes(char *str, int len)
{
	int	i;

	if (len == 2 && ((str[0] == '"' && str[1] == '"') || (str[0] == '\''
				&& str[1] == '\'')))
		return (1);
	if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\''
			&& str[len - 1] == '\''))
	{
		i = 1;
		while (i < len - 1)
		{
			if (str[i] != ' ' && str[i] != '\t')
				return (0);
			i++;
		}
		return (1);
	}
	return (-1);
}

int	is_empty_or_quoted_empty(char *str)
{
	int	i;
	int	len;
	int	quoted_result;

	if (!str || !str[0])
		return (1);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	quoted_result = check_empty_quotes(str, len);
	if (quoted_result != -1)
		return (quoted_result);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
