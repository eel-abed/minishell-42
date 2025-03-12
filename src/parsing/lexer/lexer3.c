/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:45:58 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/12 11:51:11 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*handle_env_value(t_env *env, t_might replace_mr, char *tmp,
		t_garbage **gc)
{
	char	*new_input;
	int		len;

	if (!env->vars->value)
	{
		len = ft_strlen(replace_mr.input) - (ft_strlen(tmp) + 1);
		new_input = ft_calloc(len + 1, 1, gc);
		ft_strncpy(new_input, replace_mr.input, replace_mr.j - 1);
		ft_strlcat(new_input, replace_mr.input + replace_mr.j + ft_strlen(tmp),
			len + 1);
	}
	else
	{
		len = ft_strlen(replace_mr.input) + ft_strlen(env->vars->value);
		new_input = ft_calloc(len + 1, 1, gc);
		new_input = ft_strncpy(new_input, replace_mr.input, replace_mr.j);
		ft_strlcat_mini(new_input, env->vars->value, len);
		ft_strlcat(new_input, replace_mr.input + replace_mr.j + ft_strlen(tmp),
			len);
	}
	return (new_input);
}
