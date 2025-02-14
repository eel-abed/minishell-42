/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 05:30:27 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/14 09:03:40 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int count_tokens(char *input)
{
    int i;
    int count;
    char quote;

    i = 0;
    count = 0;
    while (input[i])
    {
        // Skip spaces
        while (input[i] == ' ')
            i++;
        if (!input[i])
            break;
        count++;  // Found start of a token

        // Handle quotes
        if (input[i] == '\'' || input[i] == '\"')
        {
            quote = input[i];
            i++;
            while (input[i] && input[i] != quote)
                i++;
            if (input[i])
                i++;
        }
        // Handle operators
        else if (detect_operator(input[i]))
        {
            if (input[i + 1] && input[i] == input[i + 1])  // << or >>
                i += 2;
            else
                i++;
        }
        // Handle regular words
        else
            while (input[i] && input[i] != ' ' && !detect_operator(input[i]))
                i++;
    }
    printf("count = [%d]\n", count);
    return (count);
}
char	**split_mini(char *input)
{
    char	**tokens;
    int		i;
    int		start;
    int		j;

    tokens = malloc(sizeof(char *) * (count_tokens(input) + 1));
    if (!tokens || !input)
        return (NULL);
    i = 0;
    j = 0;
    start = 0;
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        start = i;
        if (input[i])
            tokens[j++] = extract_token(input, &i, &start);
    }
    tokens[j] = NULL;
    return (tokens);
}