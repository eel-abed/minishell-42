/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:42:17 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/13 00:33:34 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*replace_substring(char *str, t_range pos, char *replacement,
		t_garbage **gc)
{
	int		len;
	char	*result;

	if (!str || !replacement)
		return (NULL);
	len = ft_strlen(str) - (pos.end - pos.start) + ft_strlen(replacement);
	result = gc_malloc(gc, sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_strncpy(result, str, pos.start);
	ft_strlcat(result, replacement, len + 1);
	ft_strlcat(result, str + pos.end, len + 1);
	return (result);
}

char	*handle_exit_status(char *input, int *i, t_command *cmd, t_garbage **gc)
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

char	*remove_only_quotes(char *input, int j, t_garbage **gc)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(input, 0, j + 1, gc);
	tmp2 = ft_substr(input, j + 2, ft_strlen(input) - j - 2, gc);
	return (ft_strjoin(tmp, tmp2, gc));
}

char	*ft_clean_the_echo(char *input, t_garbage **gc)
{
	int	j;

	j = 0;
	while (input[j])
	{
		if (input[j] == '$' && input[j + 1] && (input[j + 1] == '"' || input[j
					+ 1] == '\''))
		{
			if (ft_isalpha(input[j + 2]))
				input = remove_dollar_quotes(input, j, gc);
			else
				input = remove_only_quotes(input, j, gc);
			j = -1;
		}
		j++;
	}
	return (input);
}

char	*any_env(char *input, t_env *env, t_garbage **gc, t_command *cmd)
{
	int		i;
	char	quote;

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
