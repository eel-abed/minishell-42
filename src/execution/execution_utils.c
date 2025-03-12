/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 18:36:47 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/12 13:36:10 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_builtin(char *cmd, t_tokens *tokens, t_command *cmd_info,
		t_garbage **gc)
{
	if (!ft_strncmp(cmd, "cd", 2))
		cd_builtin(tokens, cmd_info->env, cmd_info, gc);
	else if (!ft_strncmp(cmd, "pwd", 3))
		pwd_builtin();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo_builtin_tokens(tokens);
	else if (!ft_strncmp(cmd, "env", 3))
		env_builtin(cmd_info->env);
	else if (!ft_strncmp(cmd, "exit", 4))
		exit_builtin(tokens, cmd_info, gc);
	else if (!ft_strncmp(cmd, "export", 6))
		export_builtin(tokens, cmd_info->env, gc, cmd_info);
	else if (!ft_strncmp(cmd, "unset", 5))
		unset_builtin(tokens, cmd_info->env, cmd_info, gc);
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"echo") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
		return (true);
	return (false);
}

int	count_words_with_quotes(const char *s, char c)
{
	int		count;
	int		i;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && (s[i] != c || quote))
		{
			if ((s[i] == '"' || s[i] == '\'') && !quote)
				quote = s[i];
			else if (s[i] == quote)
				quote = 0;
			i++;
		}
	}
	return (count);
}

int	contain_echo_token(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (!ft_strcmp(tmp->value, "echo"))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
