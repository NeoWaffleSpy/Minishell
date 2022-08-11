/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/28 19:16:05 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_dist(char *str, char c)
{
	return (ft_strchr(str, c) - str);
}

int	check_valid_name(t_var *var, char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && !(str[0] == '_' && str[1] != '='))
	{
		var->exit_status = call_error("export: Invalid identifier", str, 1);
		return (0);
	}
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
		{
			var->exit_status = call_error("export: Invalid identifier",
					str, 1);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	loop_var(t_var *var, char *str)
{
	char	*name;
	char	*attr;
	int		dist;

	attr = NULL;
	dist = get_dist(str, '=');
	name = ft_substr(str, 0, dist);
	if (str[dist + 1])
	{
		attr = ft_substr(str, dist + 1, get_dist(str, '\0'));
		ft_manually_add_one_env(var->env, name, attr);
		free_garbage(attr);
	}
	else
		ft_manually_add_one_env(var->env, name, "");
	free_garbage(name);
}

void	export_var(t_var *var, t_command *comm)
{
	int		i;
	t_file	*arg;

	i = 0;
	arg = ft_lstfget(comm->arguments, i);
	while (arg)
	{
		if (arg->is_append)
			var->exit_status = call_error("export: Invalid option:",
					arg->filename, 1);
		else if (check_valid_name(var, arg->filename)
			&& ft_strchr(arg->filename, '='))
			loop_var(var, arg->filename);
		i++;
		arg = ft_lstfget(comm->arguments, i);
	}
}
