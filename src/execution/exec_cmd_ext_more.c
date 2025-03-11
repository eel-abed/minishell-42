/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:53:27 by eel-abed          #+#    #+#             */
/*   Updated: 2025/03/11 16:02:02 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	wait_for_child(pid_t pid)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
	else
		exit_code = 1;
	return (exit_code);
}

t_env_var	*get_path_variable(t_env *env)
{
	t_env_var	*path_var;

	if (!env)
	{
		return (NULL);
	}
	if (!env->vars)
	{
		return (NULL);
	}
	path_var = env->vars;
	while (path_var)
	{
		if (path_var->key && ft_strncmp(path_var->key, "PATH", 4) == 0)
			return (path_var);
		path_var = path_var->next;
	}
	return (NULL);
}

char	*extract_first_cmd(char **parts)
{
	int	i;

	i = 0;
	while (parts[i] && is_redir_operator(parts[i]))
		i += 2;
	return (parts[i]);
}

void	execute_cmd(t_tokens *cmd_token, char **parts, t_command *cmd_info,
		t_garbage **gc)
{
	char	*first_command;

	first_command = extract_first_cmd(parts);
	if (is_builtin(first_command))
		execute_builtin(first_command, cmd_token, cmd_info, gc);
	else
		cmd_info->exit_status = execute_external_command(cmd_token, cmd_info,
				gc);
}

char	*extract_word(const char *s, int *i, char c, t_garbage **gc)
{
	int		start;
	int		len;
	char	quote;
	char	*word;

	quote = 0;
	start = *i;
	len = 0;
	while (s[*i] && (s[*i] != c || quote))
	{
		if ((s[*i] == '"' || s[*i] == '\'') && !quote)
			quote = s[*i];
		else if (s[*i] == quote)
			quote = 0;
		(*i)++;
		len++;
	}
	word = ft_substr(s, start, len, gc);
	return (word);
}
