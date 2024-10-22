/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:13:37 by eel-abed          #+#    #+#             */
/*   Updated: 2024/10/22 16:15:54 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

bool	is_builtin(char *cmd);
void	execute_builtin(char *cmd, char **args);
void	cd_builtin(char **args);
void	pwd_builtin(void);
void	echo_builtin(char **args);
void	env_builtin(void);
void	exit_builtin(char **args);
void	export_builtin(char **args);
void	unset_builtin(char **args);


#endif
