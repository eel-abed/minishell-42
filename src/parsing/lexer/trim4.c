/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafourni <mafourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:28:48 by mafourni          #+#    #+#             */
/*   Updated: 2025/03/04 18:52:17 by mafourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_tokens	*ft_trim_all(t_tokens *tokens, t_garbage **gc)
{
	t_tokens	*current;
	char		*trimmed;
	int			in_export;
	int			is_echo;

	if (!tokens)
		return (NULL);
	current = tokens;
	in_export = 0;
	is_echo = is_echo_cmd(current->value, gc);
	while (current)
	{
		if (current->value)
		{
			if (is_export_cmd(current->value, gc))
			{
				trimmed = get_clean_word(current->value, gc);
				current->value = trimmed;
				in_export = 1;
			}
			else if (current->type == kind_pipe)
				in_export = 0;
			else if (in_export)
				ft_trim_export(current, gc);
			// else if (is_echo == 1)
			// {
			// 	i = 1;
			// 	closed = -1;
			// 	y = 0;
			// 	while (current->value[i])
			// 	{
			// 		if (current->value[i] == '\'' && y == 0)
			// 		{
			// 			y = 1;
			// 			closed = 0;
			// 		}
			// 		if (current->value[i] == '"' && y == 0)
			// 		{
			// 			y = 2;
			// 			closed = 0;
			// 		}
			// 		if (current->value[i] && y > 0)
			// 		{
			// 			if ((closed == 0 && i < ft_strlen(current->value) - 1
			// 					&& ((y == 1 && current->value[i] == '\'')
			// 							|| (y == 2
			// 							&& current->value[i] == '"')))
			// 							|| (closed == 1 && ((y == 1
			// 							&& current->value[i] == '\'') || (y == 2
			// 							&& current->value[i] == '"'))))
			// 			{
			// 				before = ft_substr(current->value, 0, i, gc);
			// 				after = ft_substr(current->value, i + 1,
			// 						ft_strlen(current->value) - i, gc);
			// 				trimmed = ft_strjoin(before, after, gc);
			// 				current->value = trimmed;
			// 				if (closed == 0)
			// 					closed = 1;
			// 				else
			// 				{
			// 					closed = -1;
			// 					y = 0;
			// 				}
			// 				i--;
			// 			}
			// 		}
			// 		i++;
			// 	}
			// }
			else if (!in_export && (has_attached_quotes(current->value)
					|| should_trim_quotes(current->value)))
			{
				trimmed = remove_outer_quotes(current->value, gc);
				current->value = trimmed;
			}
		}
		current = current->next;
	}
	return (tokens);
}

int	is_export_cmd(char *str, t_garbage **gc)
{
	char	*outer_quotes_removed;
	char	*clean_str;
	int		result;

	if (!str)
		return (0);
	outer_quotes_removed = remove_outer_quotes(str, gc);
	if (!outer_quotes_removed)
		return (0);
	clean_str = get_clean_word(outer_quotes_removed, gc);
	if (!clean_str)
		return (0);
	result = !ft_strcmp(clean_str, "export");
	return (result);
}

int	is_echo_cmd(char *str, t_garbage **gc)
{
	char	*outer_quotes_removed;
	char	*clean_str;
	int		result;

	if (!str)
		return (0);
	outer_quotes_removed = remove_outer_quotes(str, gc);
	if (!outer_quotes_removed)
		return (0);
	clean_str = get_clean_word(outer_quotes_removed, gc);
	if (!clean_str)
		return (0);
	result = !ft_strcmp(clean_str, "echo");
	return (result);
}

void	ft_if_loop(int *x, int *y, t_tokens *current, int i)
{
	if (current->value[i] == '"' && *y == 0)
		*y = 1;
	if (current->value[i] == '\'' && *y == 0)
		*y = 2;
	if ((*y == 1 && current->value[i] == '"') || (*y == 2
			&& current->value[i] == '\''))
		*x += 1;
}
