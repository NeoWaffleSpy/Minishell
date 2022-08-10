/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:32:34 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/28 21:32:49 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	clear_spaces(char **str)
{
	while (*str && **str && (**str == ' ' || **str == 9))
		(*str)++;
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

static int	get_clean_len(char *old)
{
	char	*str;
	int		i;
	t_var	var;

	reset_var(&var);
	i = 0;
	str = old;
	while (*str)
	{
		clear_spaces(&str);
		if (!*str)
			break ;
		i++;
		while (*str && ((*str != ' ' && *str != 9)
				|| (var.quotes % 2 || var.dquotes % 2)))
		{
			isquote(*str, &var);
			i++;
			str++;
		}
	}
	return (i);
}

static void	clean_2(char *new, char *str)
{
	int		i;
	t_var	var;

	i = 0;
	reset_var(&var);
	while (*str)
	{
		while (*str && ((*str != ' ' && *str != 9)
				|| (var.quotes % 2 || var.dquotes % 2)))
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

char	*clean_str(char *old)
{
	char	*new;
	char	*str;
	int		i;

	if (!*old)
		return (NULL);
	str = old;
	i = get_clean_len(old);
	new = malloc_garbage(sizeof(char) * i);
	ft_bzero(new, i);
	clear_spaces(&str);
	clean_2(new, str);
	free_garbage(old);
	return (new);
}
