/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2025/02/08 01:38:17 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int g_exit_status;

int main(int argc, char **argv, char **envp) 
{
    t_list  *token_clean;
    char *input;
    t_env *env;
    t_command cmd;

    (void)argc;
    (void)argv;

    env = init_env(envp);
    if (!env)
        return 1;

    setup_signals();
    ft_memset(&cmd, 0, sizeof(t_command));
    cmd.env = env;
    while (1) 
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (strlen(input) > 0) 
        {
            add_history(input);
            token_clean = ft_lexer(input);
            if(token_clean == NULL)
                (printf("CHECH\n"));
            // printf("Tu le sais %d \n",token_clean->index);
            // char **args = ft_split(input, ' ');
            // cmd.cmd1 = NULL;
            // cmd.cmd2 = NULL;
            // execute_command(args, &cmd);
            // // Add cleanup for args
            // int i = 0;
            // while (args[i]) {
            //     free(args[i]);
            //     i++;
            // }
            // free(args);
        }
        free(input);
    }

    free_env(env);
    printf("\nExiting minishell...\n");
    return 0;
}
