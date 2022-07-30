/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:12:47 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/30 21:17:56 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_buffalloc(char *str, char c)
{
	int		buffsize;
	char	*tmp;

	buffsize = 50;
	if (!str)
	{
		str = malloc_garbage(sizeof(char) * (buffsize + 1));
		ft_bzero(str, buffsize + 1);
	}
	else if (ft_strlen(str) % buffsize == 0)
	{
		tmp = malloc_garbage(sizeof(char) * (ft_strlen(str) + buffsize + 1));
		ft_bzero(tmp, ft_strlen(str) + buffsize + 1);
		ft_strcpy(tmp, str);
		free_garbage(str);
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

void	replace_tilde(char **tmp, char **res, int pos)
{
	char	*env;

	if ((pos == 0 || *((*tmp) - 1) == ' ') && (*((*tmp) + 1) == ' '
			|| *((*tmp) + 1) == '/' || *((*tmp) + 1) == 0))
	{
		env = getenv("HOME");
		if (env)
		{
			(*tmp)++;
			cpy_str(res, env);
		}
	}
	return ;
}
