/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:33:27 by eel-abed          #+#    #+#             */
/*   Updated: 2024/11/05 14:02:14 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Fonction pour libérer un tableau de chaînes de caractères
void free_string_array(char **array)
{
    int i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

// Fonction pour chercher dans PATH
char *find_command_path(char *cmd)
{
    char *path;
    char **paths;
    char *full_path;
    int i;

    // Si la commande contient déjà un chemin
    if (cmd[0] == '/' || cmd[0] == '.')
        return (ft_strdup(cmd));

    // Obtenir la variable PATH
    path = getenv("PATH");
    if (!path)
        return (NULL);

    // Split PATH en tableau de chemins
    paths = ft_split(path, ':');
    if (!paths)
        return (NULL);

    // Chercher dans chaque dossier
    i = 0;
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, cmd);
        if (access(full_path, F_OK | X_OK) == 0)
        {
            free_string_array(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free_string_array(paths);
    return (NULL);
}

int execute_external_command(char **args)
{
    pid_t pid;
    int status;
    char *cmd_path;

    if (!args || !args[0]) // Vérification si args est vide
        return (1);

    // Fork un nouveau processus
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (1);
    }
    
    if (pid == 0) // Processus enfant
    {
        // Chercher le chemin de la commande
        cmd_path = find_command_path(args[0]);
        if (!cmd_path)
        {
            ft_putstr_fd("command not found: ", 2);
            ft_putendl_fd(args[0], 2);
            exit(127);
        }
        
        // Exécuter la commande
        if (execve(cmd_path, args, environ) == -1)
        {
            perror("execve");
            free(cmd_path); // Libérer cmd_path avant de quitter
            exit(126);
        }
        free(cmd_path); // Libérer cmd_path si execve réussit
    }
    else // Processus parent
    {
        // Attendre la fin du processus enfant
        waitpid(pid, &status, 0);
        // Retourner le code de sortie directement
        return (status);
    }
    return (0);
}
