/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:06:29 by maxencefour       #+#    #+#             */
/*   Updated: 2024/12/31 11:51:59 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *input;
    (void)argc;
    (void)argv;
    (void)envp;

    setup_signals();

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;  // EOF (Ctrl+D) was entered

        if (strlen(input) > 0)
        {
            add_history(input);

            // Split input into command and arguments
            char **args = ft_split(input, ' ');

            // Appel à la nouvelle fonction pour exécuter la commande
            execute_command(args);

            // Free the arguments array
            for (int i = 0; args[i]; i++)
                free(args[i]);
            free(args);
        }

        free(input);
    }

    printf("\nExiting minishell...\n");
    return 0;
}
