/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:18:15 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/07 19:15:10 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list  *ft_lexer(char *input)
{
    t_list  *token_list;
    char *temp = input;
    token_list = NULL;
    if (quote_check(temp) == 0)
        return(printf("Syntax error\n"),NULL)
    // if (check_syntax(temp))
    //     retunr(printf())
}

int quote_check(char *input)
{
    int i;
    int j;
    int d_flag;
    int s_flag;

    j = 0;
    i = 0;
    d_flag = -1;
    s_flag = -1;
    while(input[i] != NULL)
    {
        if (input[i] = '"')
        {
			j = i;
            d_flag = 0;
            while(input[j] || d_flag == -1)
            {
			    if (input[j] = '"')
            	    d_flag = -1;
			j++;
			}
        }
        if (input[i] = 39)
        {
            j = i;
            s_flag = 0;
            while(input[i] || s_flag == -1)
            {
			if (input[i] = '"')
            	s_flag = -1;
			i++;
			}
        }
        i++;
    }   
    if (d_flag != -1 || s_flag != -1)
        return(1);
    else
        return (0);
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