/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:02:55 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 20:31:50 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	selec_ope(t_var *var, t_command *comm)
{
	if (!ft_strcmp(comm->command, "cd"))
		cd();
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
		var->exit_loop = FALSE;
	else
	{
		var->exit_status = 127;
		call_error("Command not recognized:", comm->command);
	}
	return (0);
}

int	check_valid_path(char *path)
{
	(void)path;
	call_todo("check_valid_path");
	return (0);
}

static int	tester(t_command *comm)
{
	char	*c;

	c = comm->command;
	if (!ft_strcmp(c, "<") || !ft_strcmp(c, "<<")
		|| !ft_strcmp(c, ">") || !ft_strcmp(c, ">>") || !ft_strcmp(c, "<>"))
		return (call_error("Invalid operation", comm->command));
	if (c[1] == '>' || c[1] == '<')
		return (call_error("Unknown operation", comm->command));
	if (ft_strchr(c, '/'))
	{
		if (!check_valid_path(c))
			return (call_error(c, "No such file or directory"));
		ft_printf_fd(comm->outfile, "%s: Is a directory\n", c);
		return (1);
	}
	return (0);
}

int	selector(t_var *var, char *operation)
{
	t_command	*comm;
	int			ret;

	ret = 0;
	comm = fill_command(operation);
	if (comm->command != NULL && ft_strcmp(comm->command, ":")
		&& ft_strcmp(comm->command, "!") && !tester(comm))
		ret = selec_ope(var, comm);
	free_command(&comm);
	if (ret)
		return (1);
	return (0);
}
