/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:18:15 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/07 16:10:34 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list  *ft_lexer(char *input)
{
    t_list  *token_list;
    char *temp = input;
    token_list = NULL;
    if (quote_check(temp))
        return(printf("Syntax error\n"),1)
    if (check_syntax(temp))
        retunr(printf())
}


int quote_check(char *input)
{
    int i;
    int j;
    int d_up;

    j = 0;
    i = 0;
    d_up = -1;
    while(input[i] != NULL)
    {
        if (input[i] = '"')
        {
			j = i;
            d_up = 0;
            while(input[j] || d_up == -1)
            {
			if (input[j] = '"')
            	d_up = -1;
			j++;
			}
        }
    }    
}

int check_syntax(char *input)
{
    int i;
    i = 0;
    while (input != NULL)
    {
        int j = 0;
        if(input[i] = '>')
            {
                j = i;
                while(input[j])
                    
            }
        i++;
    }
}