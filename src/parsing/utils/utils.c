/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:50:05 by mafourni          #+#    #+#             */
/*   Updated: 2025/02/14 07:17:52 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int skip_space (char *input, int i)
{
	int j = i + 1;
	while(input[j] == 32 && input[j])
		j++;
	return(j);
}

bool is_space (char *input, int i)
{
    if (input[i] == 32)
        return true;
    return false;
}

char *ft_strlcat_mini(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	// size_t	srclen;
	size_t	i;

	if (!dst)
		return (0);
	dstlen = ft_strlen(dst) - 1; // ya le -1 pour ecrire sur le $ car len compte \0
	// printf("dst len = [%ld]\n",dstlen);
	// srclen = ft_strlen(src);
	i = 0;
	if (dstsize <= dstlen)
	{
		// printf("jreteun null\n");
		return (NULL);
	}
	while (src[i] && dstlen + i < dstsize - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dst);
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

char	*ft_strcpy(char *dest, char *src, int i, int j)
{
    int index;

    index = 0;
    int len = i-j;
    dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
	    return(NULL);
	while (index < len)
	{
		dest[index] = src[j];
		j++;
        index++;
	}
	dest[index] = '\0';
	return (dest);
}

int detect_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
}
void print_tokens(t_tokens *list)
{
    t_tokens *current;
    int i;

    if (!list)
    {
        printf("Token list is empty\n");
        return ;
    }
    i = 0;
    current = list;
    while (list)
    {
        printf("Token[%d]:\n", i);
        printf("  Value: [%s]\n", list->value);
        printf("  Type:  [%d]\n", list->type);
        printf("  Addr:  [%p]\n", list);
        printf("  Next:  [%p]\n", list->next);
        printf("  Prev:  [%p]\n", list->prev);
        printf("------------------------\n");
        list = list->next;
        i++;
    }
	list = current;
}