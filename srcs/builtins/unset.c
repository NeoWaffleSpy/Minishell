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
	t_list	*arg;

	if (comm->options)
	{
		var->exit_status = call_error("unset: Invalid option:",
				comm->options->content, 1);
		return ;
	}
	i = 0;
	arg = ft_lstget(comm->arguments, i);
	while (arg)
	{
		if (check_valid_name(var, arg->content)
			&& !ft_strchr(arg->content, '='))
			ft_cleanly_delone_env(&var->env,
				ft_find_env_elem(var->env, arg->content));
		else if (ft_strchr(arg->content, '='))
			var->exit_status = call_error("export:1 Invalid identifier",
					arg->content, 1);
		i++;
		arg = ft_lstget(comm->arguments, i);
	}
}
