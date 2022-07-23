/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:48 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 16:57:57 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_var(t_var *var, t_command *comm)
{
	int		i;
	char	**split;

	if (comm->options)
	{
		var->exit_status = call_error("unset: Invalid option:", comm->options);
		return ;
	}
	i = 0;
	split = ft_split(comm->arguments, ' ');
	while (split[i])
	{
		if (check_valid_name(var, split[i]) && !ft_strchr(split[i], '='))
			ft_cleanly_delone_env(&var->env,
				ft_find_env_elem(var->env, split[i]));
		else if (ft_strchr(split[i], '='))
			var->exit_status = call_error("export:1 Invalid identifier",
					split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}
