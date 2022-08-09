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

static void	check_single_char_replace(t_var *var, char **tmp, char **res)
{
	char	*str;

	if (**tmp == ' ')
	{
		*res = ft_buffalloc(*res, '$');
		return ;
	}
	if (**tmp == '0')
		cpy_str(res, "minishell");
	if (**tmp == '?')
	{
		str = ft_itoa(var->exit_status);
		cpy_str(res, str);
		free_garbage(str);
	}
	(*tmp)++;
	return ;
}

static void	doll_search(t_var *var, char **tmp, char **res)
{
	char	*ttadd;
	int		len;
	t_env	*env;

	ttadd = NULL;
	(*tmp)++;
	if (ft_isdigit(**tmp) || **tmp == ' ' || **tmp == '?')
		return (check_single_char_replace(var, tmp, res));
	if (**tmp != ' ' && !ft_isdigit(**tmp))
	{
		len = 0;
		while ((*tmp)[len] && (*tmp)[len] != ' ' && (*tmp)[len] != '\"' && (*tmp)[len] != '\'')
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
	if (comm->options)
	{
		if (ft_strcmp(comm->options->content, "-n") == 0)
			iter_echo(comm->options, 1, 1);
		else
			iter_echo(comm->options, 0, 1);
	}
	if (comm->arguments)
		iter_echo(comm->arguments, 0, 1);
	ft_printf_fd(1, "\b");
	if (comm->options && !ft_strcmp(comm->options->content, "-n"))
		return ;
	ft_printf_fd(1, "\n");
}
