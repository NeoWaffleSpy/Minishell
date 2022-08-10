/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:48 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/28 19:16:37 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_var(t_var *var, t_command *comm)
{
	int		i;
	t_file	*arg;

	i = 0;
	arg = ft_lstfget(comm->arguments, i);
	while (arg)
	{
		if (arg->is_append)
			var->exit_status = call_error("unset: Invalid option:", arg->filename, 1);
		else if (check_valid_name(var, arg->filename)
			&& !ft_strchr(arg->filename, '='))
			ft_cleanly_delone_env(&var->env,
				ft_find_env_elem(var->env, arg->filename));
		else if (ft_strchr(arg->filename, '='))
			var->exit_status = call_error("export:1 Invalid identifier",
					arg->filename, 1);
		i++;
		arg = ft_lstfget(comm->arguments, i);
	}
}
