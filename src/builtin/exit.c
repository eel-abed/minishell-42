/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:53:56 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/25 18:51:33 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	exit_builtin(t_tokens *tokens, t_command *cmd, t_garbage **gc)
{
	int		exit_status;
	char	**args;

	args = ft_split(tokens->value, ' ', gc);
	if (!args)
		return ;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!args[1])
	{
		exit_status = cmd->exit_status;
		gc_free_all(gc);
		exit(exit_status);
	}
	if (!is_valid_number(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		gc_free_all(gc);
		exit(2);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		cmd->exit_status = 1;
		return ;
	}
	exit_status = (unsigned char)ft_atoll(args[1]);
	gc_free_all(gc);
	exit(exit_status);
}
