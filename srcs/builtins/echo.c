/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:17 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/30 21:18:44 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	doll_search(t_var *var, char **tmp, char **res);

static void	check_single_char_replace(t_var *var, char **tmp, char **res)
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
	{
		return ;
		(*tmp)++;
	}
	else
		*res = ft_buffalloc(*res, '$');
	if (**tmp == '$' )
		doll_search(var, tmp, res);
	return ;
}

static void	doll_search(t_var *var, char **tmp, char **res)
{
	char	*ttadd;
	int		len;
	t_env	*env;

	ttadd = NULL;
	(*tmp)++;
	if (!ft_isalpha(**tmp) || **tmp == '?')
		return (check_single_char_replace(var, tmp, res));
	if (**tmp != ' ' && !ft_isdigit(**tmp))
	{
		len = 0;
		while ((*tmp)[len] && (ft_isalnum((*tmp)[len]) || (*tmp)[len] == '_'))
			len++;
		ttadd = ft_substr(*tmp, 0, len);
		env = ft_find_env_elem(var->env, ttadd);
		if (env)
			cpy_str(res, env->content);
		free_garbage(ttadd);
		(*tmp) += len;
	}
}

void	replace_dollar(t_var *var, char **replace, int is_only_var)
{
	char	*tmp;
	char	*res;

	if (*replace == NULL)
		return ;
	tmp = (*replace) - 1;
	res = NULL;
	if (!ft_strchr(*replace, '$') && !ft_strchr(*replace, '~'))
		return ;
	while (*(++tmp))
	{
		if (!is_only_var && !(var->quotes % 2) && *tmp == '~')
			replace_tilde(&tmp, &res, tmp - *replace);
		if (!(var->quotes % 2) && *tmp == '$')
			doll_search(var, &tmp, &res);
		if (!(var->dquotes % 2) && *tmp == '\'')
			var->quotes++;
		else if (!(var->quotes % 2) && *tmp == '\"')
			var->dquotes++;
		res = ft_buffalloc(res, *tmp);
		if (!*tmp)
			break ;
	}
	free_garbage(*replace);
	*replace = res;
}

static void	iter_echo(t_list *lst, int i, int fd)
{
	t_list	*arg;

	arg = ft_lstget(lst, i);
	while (arg)
	{
		ft_printf_fd(fd, "%s ", arg->content);
		i++;
		arg = ft_lstget(lst, i);
	}
}

void	ft_echo(t_command *comm)
{
	int	i;
	int j;
	int	no_nl;
	char	*tmp;

	no_nl = FALSE;
	if (comm->options)
	{
		tmp = comm->options->content;
		i = 1;
		j = 0;
		while (tmp && tmp[i])
		{
			if (tmp[i] != 'n')
			{
				iter_echo(comm->options, j, 1);
				break ;
			}
			else if (i == (int)ft_strlen(tmp) - 1)
			{
				j++;
				i = 0;
				no_nl = TRUE;
				if (!ft_lstget(comm->options, j))
					break;
				tmp = ft_lstget(comm->options, j)->content;
			}
			i++;
		}
	}
	if (comm->arguments)
		iter_echo(comm->arguments, 0, 1);
	ft_printf_fd(1, "\b");
	if (no_nl)
		return ;
	ft_printf_fd(1, "\n");
}
