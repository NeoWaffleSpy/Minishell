/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:02:55 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/05 17:50:07 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	heredoc_unlink(t_command *comm)
{
	t_file		*tmp;
	t_command	*new_comm;

	new_comm = comm;
	while (new_comm)
	{
		tmp = new_comm->infile;
		while (new_comm->error == 0 && tmp)
		{
			if (tmp->is_append)
			{
				unlink(tmp->filename);
			}
			tmp = tmp->next;
		}
		new_comm = new_comm->next;
	}
}

int	selector(t_var *var, char *operation)
{
	t_command	*comm;
	int			ret;

	init_signal2();
	ret = 0;
	comm = fill_command(var, operation);
	if (var->exit_status != 130 && (comm->error != 0 || !comm->command))
	{
		var->exit_status = comm->error;
	}
	else if (var->exit_status != 130 && comm->command != NULL)
		ret = pipex(var, comm, ft_env_to_char(var->env));
	heredoc_unlink(comm);
	free_command(comm);
	if (ret)
		return (1);
	return (0);
}
