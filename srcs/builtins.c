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

static int	selec_ope(t_var *var, t_command *comm)
{
	if (!ft_strcmp(comm->command, "cd"))
		cd(var, comm);
	else if (!ft_strcmp(comm->command, "echo"))
		ft_echo(comm);
	else if (!ft_strcmp(comm->command, "pwd"))
		print_pwd(var, comm);
	else if (!ft_strcmp(comm->command, "export"))
		export_var(var, comm);
	else if (!ft_strcmp(comm->command, "unset"))
		unset_var(var, comm);
	else if (!ft_strcmp(comm->command, "env"))
		ft_print_env(var->env, comm);
	else if (!ft_strcmp(comm->command, "exit"))
		exit_mini(var, comm);
	else
		var->exit_status = call_error("Command not recognized:",
				comm->command, 127);
	return (0);
}

static void	heredoc_loop(t_var *var, t_command *comm)
{
	t_file	*tmp;

	tmp = comm->infile;
	while (comm->error == 0 && tmp)
	{
		if (tmp->is_append)
		{
			if (ft_strchr(tmp->filename, '\'')
				|| ft_strchr(tmp->filename, '\"'))
				tmp->is_append = 2;
			create_heredoc(var, tmp);
		}
		tmp = tmp->next;
	}
}

int	selector(t_var *var, char *operation, char **envp)
{
	t_command	*comm;
	int			ret;

	(void)selec_ope;
	ret = 0;
	comm = fill_command(operation);
	heredoc_loop(var, comm);
	if (var->exit_status != 130 && (comm->error != 0 || !comm->command))
	{
		var->exit_status = comm->error;
	}
	else if (var->exit_status != 130 && comm->command != NULL)
		ret = pipex(var, comm, envp);
	free_command(comm);
	if (ret)
		return (1);
	return (0);
}
