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

void	reset_var(t_var *var)
{
	var->quotes = 0;
	var->dquotes = 0;
}

int	file_create(t_command *comm, int *is_bool, char *split)
{
	int	fd;

	if (!comm->is_unaccess)
	{
		if (is_bool[0])
		{
			if (is_bool[1])
				fd = open(split, O_APPEND | O_CREAT | O_RDWR, 0644);
			else
				fd = open(split, O_TRUNC | O_CREAT | O_RDWR, 0644);
			if (fd != -1)
				close (fd);
			else
				comm->is_unaccess = TRUE;
		}
		else if (!is_bool[2] || access(split, R_OK) == -1)
			comm->is_unaccess = TRUE;
	}
	return (1);
}
