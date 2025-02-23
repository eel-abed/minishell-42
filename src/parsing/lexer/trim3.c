/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:57:33 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/23 21:58:05 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void ft_if_loop(int *x, int *y, t_tokens *current, int i)
{
    if (current->value[i] == '"' && *y == 0)
    {
        *y = 1;
    }
    if (current->value[i] == '\'' && *y == 0)
    {
        *y = 2;
    }
    if ((*y == 1 && current->value[i] == '"') || (*y == 2 && current->value[i] == '\''))
    {
        *x += 1;
    }    

}

void ft_error_export_clean_loop(t_tokens *current, int i, char *trimmed, char *clen_trimmed)
{
    // (void)current;
    // (void)i;
    // (void)trimmed;
    // (void)clen_trimmed;
    clen_trimmed = ft_strjoin(ft_substr(current->value, 0, i), trimmed);
    free(current->value);
    free(trimmed);
    current->value = clen_trimmed;
    // return 1;
}

void ft_clean_words_export(t_tokens *current)
{
    int i = 0;
    int x = 0;
    int y = 0;
    char *trimmed;
    char *clen_trimmed;
    
    clen_trimmed = NULL;
    while (current->value[i] && current->value[i + 1])
    {
        ft_if_loop(&x, &y, current, i);
        if (x % 2 == 0  && y != 0)
        {
            trimmed = ft_substr(current->value, i + 2, ft_strlen(current->value) - i);
            y = 0;
            if (current->value[i+1] == '"' && y == 0)
            {
                y = 1;
            }
            if (current->value[i+1] == '\'' && y == 0)
            {
                y = 2;
            }
            ft_error_export_clean_loop(current, i, trimmed, clen_trimmed);
            x= 1;
        }
        i++;
    }
}

// ! "And a quote at the end y a quote at the start"
void ft_export_clean_and(t_tokens *current, char *trimmed, char *tem)
{
    printf("diego orriginal ---> %s\n", current->value);
    if (current->value[0] == '\'')
    {
        tem = ft_substr(current->value, 1, ft_strlen(current->value) - 1);
        free(current->value);
        current->value = tem;	
        printf("diego first corte---> %s\n", current->value);
    }
    if (current->value[0] != '"')
    {
        trimmed = ft_strjoin("\"", current->value);
        free(current->value);
        current->value = trimmed;
        printf("diego three corte---> %s\n", current->value);
    }

    if (current->value[ft_strlen(current->value) - 1] == '\'')
    {
        tem = ft_substr(current->value, 0, ft_strlen(current->value) - 1);
        free(current->value);
        current->value = tem;	
        printf("diego second corte---> %s\n", current->value);
    }
    if (current->value[ft_strlen(current->value) - 1] != '"')
    {
        trimmed = ft_strjoin(current->value, "\"");
        free(current->value);
        current->value = trimmed;
        printf("diego 4 corte---> %s\n", current->value);
    }	
    
}

void ft_clean(t_tokens *current, int i)
{
    char *before_s;
    char *adfter_s; 
    char *join_before;
    char *result;
    
    before_s = ft_substr(current->value, 0, i + 1);
    adfter_s = ft_substr(current->value, i + 1, ft_strlen(current->value) - i);
    join_before = ft_strjoin(before_s, "\"");
    result = ft_strjoin(join_before, adfter_s);
    
    free(before_s);
    free(adfter_s);
    free(join_before);
    free(current->value);
    current->value = result;
    // printf("diego add new before  ---> %s\n", current->value);    
}

void ft_clean2(t_tokens *current, int i)
{
    char *before_s;
    char *adfter_s; 
    char *join_before;
    char *result;

    before_s = ft_substr(current->value, 0, i + 1);
    adfter_s = ft_substr(current->value, i + 1, ft_strlen(current->value) - i);
    join_before = ft_strjoin(before_s, "\"");
    result = ft_strjoin(join_before, adfter_s);
    free(before_s);
    free(adfter_s);
    free(join_before);
    free(current->value);
    current->value = result;
}

void ft_clean_wd(t_tokens *current, int y, int i)
{
    int find_equal;
    int x;
    
    find_equal = 0;
    x = 0;
    while (current->value[i])
    {
        printf("diego ---> %c\n", current->value[i]);
        if ((current->value[i] == '"' || current->value[i] == '=') && y == 0)
            y = 1;
        if ((y == 1 && current->value[i] == '"') || (y == 2 && current->value[i] == '\'') )
            x++;
        if (current->value[i] == '=' &&  (x == 1 || x == 0) && find_equal == 0)
        {
            printf("diego in equal ---> %c\n", current->value[i]);
            ft_clean(current, i);
            y = 1;
            i++;
            find_equal = 1;
        }
        else if (find_equal == 1 && current->value[i] == '"') 
        {
            printf("finish equal ---> %c\n", current->value[i]);
            ft_clean2(current, i);
            y = 1;
            x++;
            find_equal = 0;
        }
        i++;
    }
}


// export "diego=yes"'max=no'
// / export "diego=yes"'max=no''max=no'
// export "diego=yes"|export "max=no"
// export "quesp=hola      a12"'diego=goat' "|" export "quesp=hola      a12"'diego=goat'
void ft_trim_export(t_tokens *tokens)
{
    printf("diego in trimp export ---> %s\n", tokens->value);
    t_tokens	*current;
	char		*trimmed;

    int i = 0;
    int y = 0;

    char* tem;

	if (!tokens)
    {
		return ;
    }
	current = tokens;
    tem = NULL;
    trimmed = NULL;
    
    
    printf("diego ---> %s\n", current->value);

    ft_clean_words_export(current);

    while (current->value[i] && current->value[i + 1])
    {
        if (current->value[i] == '=' && y == 0)
        {
            y = 1;
        }
        if (current->value[i] == '\'' && current->value[i + 1] == '\'' && y == 1)
        {
            tem = ft_substr(current->value, 0, i + 1);
            trimmed = ft_substr(current->value, i + 2, ft_strlen(current->value) - i);
            free(current->value);
            current->value = ft_strjoin(tem, trimmed);
            free(tem);
            free(trimmed);
        }
        
        i++;
    }
    
    
    // ! "And a quote at the end y a quote at the start"
    ft_export_clean_and(current, trimmed, tem);

    // Todo add the quotes to the start and the end of the string
    i = 0;
    // x = 0;
    y = 0;
    ft_clean_wd(current, y, i);
}
