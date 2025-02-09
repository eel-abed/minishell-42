/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:22:50 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/09 19:21:37 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list	*ft_lexer(char *input)
{
	t_list	*token_list;
	char	*temp;

	temp = input;
	token_list = NULL;
	if (quote_check(temp) == 1)
		return (printf("Quote Syntax %s !\n",ERROR), NULL);
    printf("[QUOTE %s !]\n",OK);
    if (check_syntax(temp))
			return (printf("[SYNTAX OPE %s !]\n",OK), NULL);
	return (token_list);
}

bool	check_syntax(char *input)
{
	size_t i;
	size_t len;
	t_operator_kind maybe_kind;
	
	maybe_kind = kind_none;
	i = 0;
	len = ft_strlen(input);
	while(i < len)
	{
		if (is_operator(input[i], &maybe_kind))
		{
			if (is_valid_operator(&input[i], len - i,maybe_kind)== false)
			{				
				printf("[OPE SYNTAX %s at '%s' !]\n",ERROR, &input[i]);
                return false;
			}

		}
		++i;
	}
	
	return (true);
}
