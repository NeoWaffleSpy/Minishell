/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:32:34 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 18:19:49 by ncaba            ###   ########.fr       */
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

static int	isquote(char str, t_var *var)
{
	if (!(var->dquotes % 2) && str == '\'')
	{
		var->quotes++;
		return (1);
	}
	else if (!(var->quotes % 2) && str == '\"')
	{
		var->dquotes++;
		return (1);
	}
	return (0);
}

static void	clean_2(char *new, char *str)
{
	int		i;
	t_var	var;

	i = 0;
	reset_var(&var);
	while (*str)
	{
		while (*str && *str != ' ' && *str != '	')
		{
			if (!isquote(*str, &var))
				new[i++] = *str;
			str++;
		}
		clear_spaces(&str);
		if (*str)
			new[i++] = ' ';
	}
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
	clear_spaces(&str);
	clean_2(new, str);
	free(*old);
	*old = new;
}
