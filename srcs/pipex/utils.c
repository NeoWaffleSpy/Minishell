/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:32:32 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/10 00:55:43 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cmdlstsize(t_command *lst)
{
	int	size;

	size = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	selec_ope_pipex(t_var *main_process, t_command *var)
{
	if (!ft_strcmp(var->command, "cd"))
		cd(main_process, var);
	else if (!ft_strcmp(var->command, "echo"))
		ft_echo(var);
	else if (!ft_strcmp(var->command, "pwd"))
		print_pwd(main_process, var);
	else if (!ft_strcmp(var->command, "export"))
		export_var(main_process, var);
	else if (!ft_strcmp(var->command, "unset"))
		unset_var(main_process, var);
	else if (!ft_strcmp(var->command, "env"))
		ft_print_env(main_process->env, var);
	else if (!ft_strcmp(var->command, "exit"))
		exit_mini(main_process, var);
}

int	check_for_builtin(t_command *var)
{
	if (!ft_strcmp(var->command, "cd")
		|| !ft_strcmp(var->command, "echo") || !ft_strcmp(var->command, "echo")
		|| !ft_strcmp(var->command, "pwd") || !ft_strcmp(var->command, "export")
		|| !ft_strcmp(var->command, "unset") || !ft_strcmp(var->command, "env")
		|| !ft_strcmp(var->command, "exit"))
		return (1);
	return (0);
}

static int	check_outfile(t_command *var, t_file *outfile)
{
	while (outfile)
	{
		if (outfile->is_append)
			var->outfile_fd = open(outfile->filename, O_APPEND
					|O_CREAT | O_RDWR, 0000644);
		else
			var->outfile_fd = open(outfile->filename, O_TRUNC
					| O_CREAT | O_RDWR, 0000644);
		if (var->outfile_fd == -1 || access(outfile->filename, W_OK))
		{
			perror(outfile->filename);
			return (1);
		}
		if (outfile->next)
			close(var->outfile_fd);
		outfile = outfile->next;
	}
	return (0);
}

int	check_infile_and_outfile(t_command *var, t_file *infile, t_file *outfile)
{
	int	file_err;

	file_err = 0;
	var->infile_fd = -1;
	var->outfile_fd = -1;
	while (infile)
	{
		if (!(infile->next))
			var->infile_fd = open(infile->filename, O_RDONLY);
		if ((!(infile->next) && var->infile_fd == -1)
			|| access(infile->filename, R_OK))
		{
			perror(infile->filename);
			return (file_err + 1);
		}
		infile = infile->next;
	}
	if (outfile)
		file_err = check_outfile(var, outfile);
	return (file_err);
}
