/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:22:50 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/11 18:00:58 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list	*ft_lexer(char *input, t_env *env)
{
	t_list	*token_list;
	char	*temp;

	temp = input;
	token_list = NULL;
	if (quote_check(temp) == 1)
		return (printf("Quote Syntax %s !\n", ERROR), NULL);
	printf("[QUOTE %s !]\n", OK);
	if (check_syntax(temp) == 0)
		return (printf("OPE %s !\n", ERROR), NULL);
	printf("[QUOTEwaeqeqweqe %s !]\n", OK);
	temp = any_env(temp, env);
	return (token_list);
}

bool	check_syntax(char *input)
{
	size_t			i;
	size_t			len;
	t_operator_kind	maybe_kind;

	maybe_kind = kind_none;
	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (is_operator(input[i], &maybe_kind))
		{
			if (is_valid_operator(&input[i], len - i, maybe_kind) == false)
			{
				// printf("[OPE SYNTAX %s at '%s' !]\n", ERROR, &input[i]);
				return (false);
			}
		}
		++i;
	}
	return (true);
}

char	*ft_strcpy(char *dest, char *src, int i, int j)
{
    printf("OE\n");
    int index;

    index = 0;
    int len = i-j;
    printf("len = [%d]\n", len);
    dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
	    return(NULL);
	while (index < len)
	{
		dest[index] = src[j];
		// printf("[%c]\n", dest[index]);
		j++;
        index++;
	}
	dest[index] = '\0';
	return (dest);
}
char *any_env(char *input, t_env *env)
{
	char *tmp;
	t_env *envi;
	int i;
	int j;

	envi = env;
	printf("USELES = [%s]\n",envi->vars->key);
	i = 0;
	while(input[i])
	{
		if (input[i] == '$' && input[i])
		{ 
			i++;
			j = i;
			while(ft_isalnum(input[i]) && input[i])
				i++;
			tmp = ft_strcpy(tmp,input,i,j);
			printf("[%s]", tmp);
			might_replace(envi,input,j,tmp );
			if(!input[i])
				break;
		}
		i++;
	}
	return(input);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *might_replace(t_env *env,char *input, int j, char *tmp)
{
	printf("--[%d]---\n",j);
	while(env->vars != NULL)
	{
		if (ft_strcmp(env->vars->key,tmp) == 0)
			{
				printf("env = [%s], tmp = [%s]\n" ,env->vars->key,tmp);
				printf("FOUND\n");
				break;
			}
		// printf("[%s]",env->vars->key);
		env->vars = env->vars->next;
	}
	return (input);
}