/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:11:13 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/11 04:35:15 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	fill_matrix(char **matrix, t_file *list)
{
	int	i;

	i = 1;
	while (list->next)
	{
		matrix[i++] = (char *)list->filename;
		list = list->next;
	}
	matrix[i++] = (char *)list->filename;
	return (i);
}

static void	create_cmd_args(t_command *var, t_pipex *pipex)
{
	int	size;

	size = 1 + ft_lstfsize(var->arguments);
	pipex->cmd_arguments = (char **)malloc_garbage(sizeof(char *) * (size + 1));
	if (!(pipex->cmd_arguments))
		return ;
	pipex->cmd_arguments[size] = NULL;
	pipex->cmd_arguments[0] = var->command;
	if (var->arguments)
		fill_matrix(pipex->cmd_arguments, var->arguments);
}

static void	check_child_dup(t_pipex *pipex, t_command *var)
{
	if (var->infile)
	{
		if (dup2(var->infile_fd, 0) < 0)
			child_dup_error(pipex, var);
	}
	else if (pipex->id != 0)
	{
		if (dup2(pipex->pipefd[2 * pipex->id - 2], 0) < 0)
			child_dup_error(pipex, var);
		pipex->except1 = 2 * pipex->id - 2;
	}
	if (var->outfile)
	{
		if (dup2(var->outfile_fd, 1) < 0)
			child_dup_error(pipex, var);
	}
	else if (var->next)
	{
		if (dup2(pipex->pipefd[2 * pipex->id + 1], 1) < 0)
			child_dup_error(pipex, var);
		pipex->except2 = 2 * pipex->id + 1;
	}
}

void	child(t_var *main_process, t_pipex *pipex, t_command *var, char *envp[])
{
	init_child();
	var->pidn = 0;
	if (check_infile_and_outfile(var, var->infile, var->outfile))
	{
		close_pipes(pipex);
		free_c_process(pipex, var);
		exit (errno);
	}
	check_child_dup(pipex, var);
	close_pipes(pipex);
	if (!var->command)
		;
	else if (check_for_builtin(var))
		selec_ope_pipex(main_process, var);
	else
	{
		check_cmd_path2(pipex, var);
		create_cmd_args(var, pipex);
		execve(pipex->cmd, pipex->cmd_arguments, envp);
		perror(pipex->cmd);
	}
	free_c_process(pipex, var);
	exit (errno);
}

void	child_single(t_pipex *pipex, t_command *var, char *envp[])
{
	init_child();
	if (check_infile_and_outfile(var, var->infile, var->outfile))
	{
		free_c_process(pipex, var);
		exit (errno);
	}
	if (var->infile)
		dup2(var->infile_fd, 0);
	if (var->outfile)
		dup2(var->outfile_fd, 1);
	create_cmd_args(var, pipex);
	execve(pipex->cmd, pipex->cmd_arguments, envp);
	perror(pipex->cmd);
	free_c_process(pipex, var);
	exit (errno);
}
