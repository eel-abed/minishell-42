/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:22:50 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/08 04:10:52 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_lexer(char *input)
{
	t_list	*token_list;
	char	*temp;

	temp = input;
	token_list = NULL;
	if (quote_check(temp) == 1)
		return (printf("Syntax error !\n"), NULL);
    printf("Quote ok\n");
    if (operator_error(temp) == 1)
        return (printf("Syntax error !\n"), NULL);
	// else
	// 	return (printf("Good Operatot\n"), NULL);
	// printf("oe\n");
	return (token_list);
	// if (check_syntax(temp))
	//     retunr(printf())
}

int	quote_check(char *input)
{
	int i;
	int flag;
    char to_found;
    
	i = 0;
	flag = -1;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
            to_found = input[i];
			flag = 0;
            i++;
			while (input[i] && flag == 0)
			{
				if (input[i] == to_found)
					flag = -1;
				i++;
			}
            i--;
		}
		i++;
	}
	if (flag != -1)
		return (1);
	else
		return (0);
}

int operator_error(char *input)
{
	int value;

	value = 0;
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			
		if (input[i]== '<')

		if(input[i] == '>')

		i++;
	}
	return (value);
}
int pipe_syntax(char *input, int i)
{
	while(input[i] && input[i] == 32)
		i++;
	if (input[i] == '|' || !input[i])
		return (i--,1);
	else
		return(i--,0)
}

int skip_space (char *input, int i)
{
	int j = i + 1;
	while(input[j] == 32 && input[j])
		j++;
	return(j);
}

// bool	between_quote(char *input, int i, int pos)
// {
// 	int flag;

// 	flag = -1;
// 	char to_found;
// 	while(i != pos)
// 	{
// 		if (input[i] == "\'" || input[i] == "\"")
// 		{
// 			flag = 0;
// 			to_found = input[i];
// 			while(input[i] && input[i] != to_found)
// 			{
// 				if(input[i] = to_found && i > pos)
// 					flag = -1;
// 				i++;
// 			}
				
// 		}
// 		i--;
// 	}
// 	return (false);
// }