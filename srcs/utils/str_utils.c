/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:32:34 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/14 21:13:54 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	clear_spaces(char **str)
{
	while (*str && **str && (**str == ' ' || **str == '	'))
		(*str)++;
}

static int	get_clean_len(char *old)
{
	char	*str;
	int		i;

	i = 0;
	str = old;
	while (*str)
	{
		clear_spaces(&str);
		if (!*str)
			break ;
		i++;
		while (*str && *str != ' ' && *str != '	')
		{
			i++;
			str++;
		}
	}
	return (i);
}

void	clean_str(char **old)
{
	char	*new;
	char	*str;
	int		i;

	if (!*old)
		return ;
	str = *old;
	i = get_clean_len(*old);
	new = malloc(sizeof(char) * i);
	ft_bzero(new, i);
	i = 0;
	clear_spaces(&str);
	while (*str)
	{
		while (*str && *str != ' ' && *str != '	')
		{
			new[i++] = *str;
			str++;
		}
		clear_spaces(&str);
		if (*str)
			new[i++] = ' ';
	}
	free(*old);
	*old = new;
}
