/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:50:05 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/03 17:42:19 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	skip_space(char *input, int i)
{
	int	j;

	j = i + 1;
	while (input[j] == 32 && input[j])
		j++;
	return (j);
}

bool	is_space(char *input, int i)
{
	if (input[i] == 32)
		return (true);
	return (false);
}

char	*ft_strlcat_mini(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	i;

	if (!dst)
		return (NULL);
	dstlen = ft_strlen(dst) - 1;
	i = 0;
	if (dstsize <= dstlen)
		return (NULL);
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

void	print_tokens(t_tokens *list)
{
	t_tokens	*current;
	int			i;

	if (!list)
	{
		// printf("Token list is empty\n");
		return ;
	}
	i = 0;
	current = list;
	while (list)
	{
		// printf("Token[%d]:\n", i);
		// printf("  Value: [%s]\n", list->value);
		// printf("  Type:  [%d]\n", list->type);
		// printf("------------------------\n");
		list = list->next;
		i++;
	}
	list = current;
}
