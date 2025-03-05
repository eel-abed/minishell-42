/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:17:56 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/05 16:27:37 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*replace_null(char *input, int j, char *tmp, t_garbage **gc)
{
	char	*new_input;
	int		len;

	len = ft_strlen(input);
	new_input = ft_calloc(len + 1, 1, gc);
	if (!new_input)
		return (NULL);
	new_input = ft_strncpy(new_input, input, j - 1);
	ft_strlcat(new_input, input + ft_strlen(tmp) + j, len + 1);
	input = new_input;
	return (input);
}