/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 15:32:34 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/19 20:11:08 by ncaba            ###   ########.fr       */
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

char	*ft_buffalloc(char *str, char c)
{
	int		buffsize;
	char	*tmp;

	buffsize = 50;
	if (!str)
	{
		str = malloc(sizeof(char) * buffsize + 1);
		ft_bzero(str, buffsize + 1);
	}
	else if (ft_strlen(str) % buffsize == 0)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(str) + buffsize + 1));
		ft_bzero(str, ft_strlen(str) + buffsize + 1);
		ft_strcpy(tmp, str);
		free(str);
		str = tmp;
	}
	str[ft_strlen(str)] = c;
	return (str);
}

void	cpy_str(char **dst, char *src)
{
	if (!src)
		return ;
	while (*src)
	{
		*dst = ft_buffalloc(*dst, *src);
		src++;
	}
}
