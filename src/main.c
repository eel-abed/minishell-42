/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2024/10/21 19:14:34 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"




int main(int argc, char **argv, char **envp)
{
    char *input;
    (void)argc;
    (void)argv;
    (void)envp;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;  // EOF (Ctrl+D) was entered

        if (strlen(input) > 0)
        {
            add_history(input);
            if (is_builtin(input))
            {
                printf("'%s' is a builtin command\n", input);
            }
            else
            {
                printf("'%s' is not a builtin command\n", input);
            }
        }

        free(input);
    }

    printf("\nExiting minishell...\n");
    return 0;
}
