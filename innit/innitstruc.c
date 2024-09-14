/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innitstruc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxencefournier <maxencefournier@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:35:29 by maxencefour       #+#    #+#             */
/*   Updated: 2024/09/14 19:14:04 by maxencefour      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

t_minis	*ft_mallocstruc_minis(t_minis *innit)
{
	innit = malloc(sizeof(t_minis));
	if (!innit)
		return (0);
	return (innit);
}

t_minis	*ft_innit_minis(void)
{
	t_minis	*innit_minis;

	innit_minis = NULL;
	innit_minis = ft_mallocstruc(innit_minis);
	return (innit_minis);
}

t_token	*ft_mallocstruc_token(t_token *innit)
{
	innit = malloc(sizeof(t_token));
	if (!innit)
		return (0);
	return (innit);
}

t_token	*ft_innit_token(void)
{
	t_token	*innit_token;

	innit_token = NULL;
	innit_token = ft_mallocstruc(innit_token);
	return (innit_token);
}
