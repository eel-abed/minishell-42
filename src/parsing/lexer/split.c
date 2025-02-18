/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 05:30:27 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/18 19:33:09 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	handle_quotes(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i])
		(*i)++;
}

static void	process_token(char *input, int *i)
{
	while (input[*i] && input[*i] != ' ')
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			handle_quotes(input, i);
		else if (detect_operator(input[*i]))
			break ;
		else
			(*i)++;
	}
}

int	count_tokens(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		while (input[i] && input[i] == 32)
			i++;
		if (!input[i])
			break ;
		count++;
		if (detect_operator(input[i]))
		{
			if (input[i + 1] && detect_operator(input[i + 1])
				&& input[i] == input[i + 1])
				i += 2;
			else
				(i)++;
			continue ;
		}
		process_token(input, &i);
	}
	printf("count = %d\n", count);
	return (count);
}

char	*extract_token(char *input, int *i, int *start)
{
	char	*token;
	int		len;

	if (detect_operator(input[*i]))
	{
		len = (input[*i + 1] && detect_operator(input[*i + 1])
				&& input[*i] == input[*i + 1]) ? 2 : 1;
		token = ft_substr(input, *start, len);
		*i += len;
		return (token);
	}
	while (input[*i] && !detect_operator(input[*i]) && input[*i] != ' ')
	{
		if (input[*i] == '\'' || input[*i] == '\"')
			handle_quotes(input, i);
		else
			(*i)++;
	}
	return (ft_substr(input, *start, *i - *start));
}

char	**split_mini(char *input)
{
	char	**result;
	int		i;
	int		j;
	int		start;

	result = malloc(sizeof(char *) * (count_tokens(input)+ 1));
	if (!input || !result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_tokens(input))
	{
		while (input[i] && input[i] == ' ')
			i++;
		start = i;
		result[j] = extract_token(input, &i, &start);
		if (!result[j])
		{
			while (j > 0)
				free(result[--j]);
			return (free(result), NULL);
		}
		j++;
	}
	return (result[j] = NULL, result);
}
