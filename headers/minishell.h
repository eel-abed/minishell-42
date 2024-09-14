/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxencefournier <maxencefournier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 15:56:04 by maxencefour       #+#    #+#             */
/*   Updated: 2024/09/14 19:14:09 by maxencefour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"
# include "readline/include/readline/readline.h"
# include "readline/include/readline/history.h"


// STRUC

typedef struct  s_token
{
	int				content;
	struct s_token	*next;
	int				index;
	bool			flag;
}					t_token;

typedef struct  s_minis
{
    char            *input;
	int				content;
	struct s_mini	*next;
	int				index;
	bool			flag;
}					t_minis;

//INNIT FUNCTIONS

t_minis	*ft_mallocstruc_minis(t_minis *innit);
t_token	*ft_innit_token(void);
t_token	*ft_mallocstruc_token(t_token *innit);
t_minis	*ft_innit_minis(void);
