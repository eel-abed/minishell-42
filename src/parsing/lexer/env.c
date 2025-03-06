/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:42:17 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/06 17:12:20 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*handle_exit_status(char *input, int *i, t_command *cmd,
		t_garbage **gc)
{
	t_range	pos;
	char	*exit_status;

	exit_status = ft_itoa(cmd->exit_status, gc);
	if (!exit_status)
		return (NULL);
	pos.start = *i;
	pos.end = *i + 2;
	input = replace_substring(input, pos, exit_status, gc);
	if (input)
		*i += ft_strlen(exit_status) - 1;
	return (input);
}

static char	*handle_env_var(char *input, int *i, t_env *env, t_garbage **gc)
{
	int		j;
	char	*tmp;
	char	*result;

	j = ++(*i);
	while (ft_isalnum(input[*i]))
		(*i)++;
	if (*i == j)
		return (input);
	tmp = ft_strcpy(NULL, input, *i, j, gc);
	result = might_replace(env, input, j, tmp, gc);
	if (result && ft_strlen(result) < ft_strlen(input))
		*i -= (ft_strlen(input) - ft_strlen(result));
	if (result)
		return (result);
	return (input);
}

char	*any_env(char *input, t_env *env, t_garbage **gc, t_command *cmd)
{
	int				i;
	char		quote;

	i = 0;
	quote = 0;
	while (input && input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && !quote)
			quote = input[i];
		else if (input[i] == quote)
			quote = 0;
		else if (input[i] == '$' && quote != '\'')
		{
			if (input[i + 1] == '?')
				input = handle_exit_status(input, &i, cmd, gc);
			else
				input = handle_env_var(input, &i, env, gc);
			if (!input)
				return (NULL);
			continue ;
		}
		i++;
	}
	return (input);
}
