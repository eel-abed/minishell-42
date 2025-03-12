/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:06:41 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/13 00:33:22 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*handle_env_var_utlis(char *input, int *i, t_garbage **gc)
{
	int		j;
	char	*tmp;
	t_range	pos;

	j = *i;
	(*i)++;
	tmp = ft_itoa(getpid(), gc);
	pos.start = j - 1;
	pos.end = *i;
	input = replace_substring(input, pos, tmp, gc);
	return (input);
}

char	*handle_env_var(char *input, int *i, t_env *env, t_garbage **gc)
{
	int		j;
	char	*tmp;
	char	*result;
	t_might	replace_mr;

	j = ++(*i);
	if (input[*i] == '$')
	{
		return (handle_env_var_utlis(input, i, gc));
	}
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	if (*i == j)
		return (ft_clean_the_echo(input, gc));
	replace_mr.input = input;
	replace_mr.j = j;
	tmp = ft_strcpy(NULL, replace_mr, *i, gc);
	if (ft_isdigit(tmp[0]) || tmp[0] == '-')
		tmp = ft_substr(tmp, 0, 1, gc);
	result = might_replace(env, replace_mr, tmp, gc);
	if (result && ft_strlen(result) < ft_strlen(input))
		*i -= (ft_strlen(input) - ft_strlen(result));
	if (result)
		return (result);
	return (input);
}

char	*remove_dollar_quotes(char *input, int j, t_garbage **gc)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(input, 0, j, gc);
	tmp2 = ft_substr(input, j + 2, ft_strlen(input) - j - 3, gc);
	tmp3 = ft_strjoin(tmp, tmp2, gc);
	return (ft_strdup(tmp3, gc));
}
