/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:17:56 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 11:50:36 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*might_replace(t_env *env, t_might replace_mr, char *tmp,
		t_garbage **gc)
{
	t_env_var	*head;
	char		*new_input;

	new_input = replace_mr.input;
	head = env->vars;
	while (env->vars != NULL)
	{
		if (ft_strcmp(env->vars->key, tmp) == 0)
		{
			new_input = handle_env_value(env, replace_mr, tmp, gc);
			replace_mr.input = new_input;
			env->vars = head;
			break ;
		}
		env->vars = env->vars->next;
	}
	if (env->vars == NULL)
	{
		replace_mr.input = replace_null(replace_mr.input, replace_mr.j, tmp,
				gc);
		env->vars = head;
	}
	return (replace_mr.input);
}
