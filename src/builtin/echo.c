/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:18 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/28 18:07:18 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	is_valid_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (i > 1);
}

static void print_echo_args(char **args, int i, bool newline)
{
    while (args[i])
    {
        write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
}

void	echo_builtin(char **args)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = false;
		i++;
	}
	print_echo_args(args, i, newline);
}

void	echo_builtin_tokens(t_tokens *tokens, t_garbage **gc)
{
	bool	newline;
	char	**args;
	int		i;
	char	*cmd;

	args = ft_split(tokens->value, ' ', gc);
	if (!args)
		return ;
	cmd = args[0];
	if (ft_strncmp(cmd, "echo", 4) == 0)
		i = 1;
	else
		i = 0;
	newline = true;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = false;
		i++;
	}
	print_echo_args(args, i, newline);
}
