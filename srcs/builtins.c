/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:02:55 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/02 19:43:51 by ncaba            ###   ########.fr       */
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

int	selector(t_var *var, char *operation)
{
	t_command	*comm;
	int			ret;

	ret = 0;
	comm = fill_command(operation);
	if (comm->error == 0 && comm->delim)
		create_heredoc(comm);
	if (comm->error != 0 || !comm->command)
		var->exit_status = comm->error;
	else if (comm->command != NULL)
		ret = selec_ope(var, comm);
	free_command(comm);
	if (ret)
		return (1);
	return (0);
}
