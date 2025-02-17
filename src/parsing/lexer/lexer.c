/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 01:22:50 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/17 17:03:33 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_tokens	*ft_lexer(char *input, t_env *env)
{
	t_tokens	*token_list;
	char	*temp;

	temp = input;
	token_list = NULL;
	if (quote_check(temp) == 1)
		return (printf("Quote Syntax %s !\n", ERROR), NULL);
	printf("[QUOTE %s !]\n", OK);
	if (check_syntax(temp) == 0)
		return (printf("OPE %s !\n", ERROR), NULL);
	printf("[OPE %s !]\n", OK);
	temp = any_env(temp, env);
	token_list = lets_tokeninze(temp);
	token_list = ft_trim_all(token_list);
	printf("BEFORE PIPE  function \n");
	print_tokens(token_list);
	token_list = token_with_pipe(token_list);
	printf("AFTER PIPE function \n");
	print_tokens(token_list);
	// printf("TEMP (l'input quoi) after any_env(function) =  [%s]\n", temp);
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

char *any_env(char *input, t_env *env)
{
	t_env *envi;
	char *tmp;
	int i;
	int j;

	envi = env;
	i = 0;
	while(input[i])
	{
		// printf("index while = [%d]\n",i);
		if (input[i] == '$' && input[i])
		{
			// printf("IN\n");
			i++;
			j = i;
			while(ft_isalnum(input[i]) && input[i])
				i++;
			// printf("i apres isalnum =[%d]\n",i);
			tmp = ft_strcpy(tmp,input,i,j);
			int h = ft_strlen(input);
			input = might_replace(envi,input,j,tmp);
			if((int)ft_strlen(input) < h) //Ya pete un bug si env value et 2
				i = i - (h - (int)ft_strlen(input));
			// printf("i = [%d]\n",i);
			// printf("INPUT = [%s]\n", input);
			free(tmp);
		}
		if(input[i] && input[i] != '$')
			i++;
	}
	return(input);
}
char *might_replace(t_env *env,char *input, int j, char *tmp)
{
	char *new_input;
	t_env_var *head;
	int len;
	new_input = input;
	len = 0;
	head = env->vars;
	// printf("TMP before : while loop = [%s]\n",tmp);
	while(env->vars != NULL)
	{
		if (ft_strcmp(env->vars->key,tmp) == 0)
		{
			len = ft_strlen(input) + ft_strlen(env->vars->value);
			new_input = ft_calloc(len + 1, 1);
			if (!new_input)
				return (NULL);
			// printf("value de J = [%d]\n",j);
			new_input = ft_strncpy(new_input,input,j);
			ft_strlcat_mini(new_input,env->vars->value, len);
			ft_strlcat(new_input, input + j + ft_strlen(tmp),len);
			input = new_input;
			env->vars = head;
			break;
		}
		env->vars = env->vars->next;
	}
	if (env->vars == NULL)
	{
	len = ft_strlen(input);
	new_input = ft_calloc(len + 1, 1);
	if (!new_input)
		return (NULL);
	new_input = ft_strncpy(new_input,input,j - 1);
	// printf("new input apres strncpy = [%s]\n", new_input);
	// ft_strlcat_mini(new_input,"", len);
	// printf("new input strlcatmini = [%s]\n", new_input);
	// printf("LEN DE TMP = [%ld]\n",ft_strlen(tmp));
	ft_strlcat(new_input, input + ft_strlen(tmp)+ j,len);
	// printf("new input strlcat tou = [%s]\n", new_input);
	input = new_input;
	env->vars = head;
	}
	// printf("input = [%s]\n",input);
	return (input);
}
// salut $USER et $non existe pas