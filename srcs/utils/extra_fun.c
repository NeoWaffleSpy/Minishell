/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:28:27 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/10 19:28:28 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_child(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

int	dup2_close(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror("pipe");
			return (0);
		}
		close(oldfd);
	}
	return (1);
}

int	ft_lstfsize(t_file *list)
{
	int	size;

	if (!list)
		return (0);
	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

void	check_single_char_replace(t_var *var, char **tmp, char **res)
{
	char	*str;

	if (**tmp == '0')
	{
		cpy_str(res, "minishell");
		(*tmp)++;
	}
	else if (**tmp == '?')
	{
		str = ft_itoa(var->exit_status);
		cpy_str(res, str);
		free_garbage(str);
		(*tmp)++;
	}
	else if (ft_isdigit(**tmp))
		(*tmp)++;
	else if (!(var->dquotes % 2) && (**tmp == '\'' || **tmp == '\"'))
		;
	else
		*res = ft_buffalloc(*res, '$');
	if (**tmp == '$' )
		doll_search(var, tmp, res);
	return ;
}
