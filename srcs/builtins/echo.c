/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:17 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/19 20:39:38 by ncaba            ###   ########.fr       */
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
		cpy_str(res, "Minishell");
	if (**tmp == '?')
	{
		str = ft_itoa(var->exit_status);
		cpy_str(res, str);
		free(str);
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
		while ((*tmp)[len] && (*tmp)[len] != ' ')
			len++;
		ttadd = ft_substr(*tmp, 0, len);
		env = ft_find_env_elem(var->env, ttadd);
		if (env)
			cpy_str(res, env->content);
		free(ttadd);
		(*tmp) += len;
	}
}

void	replace_dollar(t_var *var, char **replace)
{
	char	*tmp;
	char	*res;

	tmp = (*replace) - 1;
	res = NULL;
	var->quotes = 0;
	var->dquotes = 0;
	if (!ft_strchr(*replace, '$'))
		return ;
	while (*(++tmp))
	{
		if (!(var->quotes % 2) && *tmp == '$')
			doll_search(var, &tmp, &res);
		if (!(var->dquotes % 2) && *tmp == '\'')
			var->quotes++;
		else if (!(var->quotes % 2) && *tmp == '\"')
			var->dquotes++;
		else
			res = ft_buffalloc(res, *tmp);
		if (!*tmp)
			break ;
	}
	free(*replace);
	*replace = res;
}

void	ft_echo(t_var *var, t_command *comm)
{
	char	*tmp;

	tmp = NULL;
	if (comm->options)
	{
		if (comm->options[0] == '-' && comm->options[1] == 'n')
		{
			if (comm->options[2] && comm->options[3] != ' ')
				tmp = ft_str_sp_join(&comm->options[3], comm->arguments);
			else
				tmp = ft_strdup(comm->arguments);
			replace_dollar(var, &tmp);
			ft_printf("%s%s47;1;30m%%%s\n", tmp, BASE, RESET_COLOR);
			free(tmp);
			var->exit_status = 0;
			return ;
		}
		tmp = ft_str_sp_join(comm->options, comm->arguments);
	}
	else
		tmp = ft_strdup(comm->arguments);
	replace_dollar(var, &tmp);
	ft_printf("%s\n", tmp);
	free(tmp);
	var->exit_status = 0;
}
