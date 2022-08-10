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

void	doll_search(t_var *var, char **tmp, char **res)
{
	char	*ttadd;
	int		len;
	t_env	*env;

	ttadd = NULL;
	(*tmp)++;
	if (!ft_isalpha(**tmp) || **tmp == '?' || **tmp == '\'' || **tmp == '\"')
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
		if (**tmp == '$' )
			doll_search(var, tmp, res);
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

static void	iter_echo(t_file *lst, int i, int fd)
{
	t_file	*arg;

	arg = ft_lstfget(lst, i);
	while (arg)
	{
		ft_printf_fd(fd, "%s", arg->filename);
		i++;
		arg = ft_lstfget(lst, i);
		if (arg)
			ft_printf_fd(fd, " ");
	}
}

static void	echo_loop(int *j, int *no_nl, char **tmp, t_command *comm)
{
	int	i;

	i = 1;
	while (*tmp && (*tmp)[i])
	{
		if ((*tmp)[0] != '-' || (*tmp)[i] != 'n')
			break ;
		else if (i == (int)ft_strlen(*tmp) - 1)
		{
			(*j)++;
			i = 0;
			*no_nl = TRUE;
			if (!ft_lstfget(comm->arguments, *j))
				break ;
			*tmp = ft_lstfget(comm->arguments, *j)->filename;
		}
		i++;
	}
}

void	ft_echo(t_command *comm)
{
	int		j;
	int		no_nl;
	char	*tmp;

	no_nl = FALSE;
	j = 0;
	tmp = NULL;
	if (comm->arguments)
		tmp = ft_lstfget(comm->arguments, j)->filename;
	echo_loop(&j, &no_nl, &tmp, comm);
	if (tmp)
		iter_echo(comm->arguments, j, 1);
	if (no_nl)
		return ;
	ft_printf_fd(1, "\n");
}
