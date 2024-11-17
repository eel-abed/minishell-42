/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:58:15 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/17 13:53:19 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp(cmd, "cd", 2) || !ft_strncmp(cmd, "pwd", 3)
		|| !ft_strncmp(cmd, "echo", 4) || !ft_strncmp(cmd, "env", 3)
		|| !ft_strncmp(cmd, "exit", 4) || !ft_strncmp(cmd, "export", 6)
		|| !ft_strncmp(cmd, "unset", 5))
		return (true);
	return (false);
}

void	execute_builtin(char *cmd, char **args)
{
	if (!ft_strncmp(cmd, "cd", 2))
		cd_builtin(args);
	else if (!ft_strncmp(cmd, "pwd", 3))
		pwd_builtin();
	else if (!ft_strncmp(cmd, "echo", 4))
		echo_builtin(args);
	else if (!ft_strncmp(cmd, "env", 3))
		env_builtin();
	else if (!ft_strncmp(cmd, "exit", 4))
		exit_builtin(args);
	else if (!ft_strncmp(cmd, "export", 6))
		export_builtin(args);
	else if (!ft_strncmp(cmd, "unset", 5))
		unset_builtin(args);
}

void	execute_command(char **args)
{
	int i = 0;
	char *input_file = NULL;
	char *output_file = NULL;
	bool heredoc_flag = false;
	char *delimiter = NULL;

	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 1) == 0)
		{
			input_file = args[i + 1];
			i += 2; // Passer le fichier
		}
		else if (ft_strncmp(args[i], ">", 1) == 0)
		{
			output_file = args[i + 1];
			i += 2; // Passer le fichier
		}
		else if (ft_strncmp(args[i], ">>", 2) == 0)
		{
			output_file = args[i + 1];
			i += 2; // Passer le fichier
		}
		else if (ft_strncmp(args[i], "<<", 2) == 0)
		{
			delimiter = args[i + 1];
			heredoc_flag = true;
			i += 2; // Passer le délimiteur
		}
		else
		{
			i++;
		}
	}

	if (input_file)
		redirect_input(input_file);
	if (output_file && !heredoc_flag)
		redirect_output(output_file);
	if (heredoc_flag)
		heredoc(delimiter);

	if (is_builtin(args[0]))
	{
		execute_builtin(args[0], args);
	}
	else
	{
		execute_external_command(args);
	}
}
