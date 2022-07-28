/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:02:55 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/28 16:13:26 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	selec_ope(t_var *var, t_command *comm)
{
	if (!ft_strcmp(comm->command->content, "cd"))
		cd(var, comm);
	else if (!ft_strcmp(comm->command->content, "echo"))
		ft_echo(comm);
	else if (!ft_strcmp(comm->command->content, "pwd"))
		print_pwd(var, comm);
	else if (!ft_strcmp(comm->command->content, "export"))
		export_var(var, comm);
	else if (!ft_strcmp(comm->command->content, "unset"))
		unset_var(var, comm);
	else if (!ft_strcmp(comm->command->content, "env"))
		ft_print_env(var->env, comm);
	else if (!ft_strcmp(comm->command->content, "exit"))
		exit_mini(var, comm);
	else
		var->exit_status = call_error("Command not recognized:",
				comm->command->content, 127);
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

	c = comm->command->content;
	if (!ft_strcmp(c, "<") || !ft_strcmp(c, "<<")
		|| !ft_strcmp(c, ">") || !ft_strcmp(c, ">>") || !ft_strcmp(c, "<>"))
		return (call_error("Invalid operation", c, 1));
	if (c[1] == '>' || c[1] == '<')
		return (call_error("Unknown operation", c, 1));
	if (ft_strchr(c, '/'))
	{
		if (!check_valid_path(c))
			return (call_error(c, "No such file or directory", 1));
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
	if (comm->command->content != NULL && ft_strcmp(comm->command->content, ":")
		&& ft_strcmp(comm->command->content, "!") && !tester(comm))
		ret = selec_ope(var, comm);
	free_command(&comm);
	if (ret)
		return (1);
	return (0);
}
