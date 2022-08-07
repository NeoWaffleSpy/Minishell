/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:11:13 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/06 02:22:51 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char	*find_cmd_path(char **paths, char *command, char *cmd_path)
{
	while (paths && *paths)
	{
		cmd_path = ft_strjoin(*paths, command);
		if (access(cmd_path, 0) == 0)
			return (cmd_path);
		paths++;
	}
	return (cmd_path);
}

static	char	*check_cmd_path(t_pipex *pipex)
{
	char	**paths;
	char	*command;
	char	*cmd_path;

	if (!(pipex->cmd_arguments) || !(pipex->cmd_arguments[0]))
	{
		cmd_path = ft_strjoin("", "");
		return (cmd_path);
	}
	command = ft_strjoin("/", pipex->cmd_arguments[0]);
	paths = pipex->path_list;
	cmd_path = ft_strjoin("", pipex->cmd_arguments[0]);
	if (access(cmd_path, 0) == 0)
		return (cmd_path);
	return (find_cmd_path(paths, command, cmd_path));
}

static int	fill_matrix(char **matrix, t_list *list, int i)
{
	while (list->next)
		matrix[i++] = (char *)list->content;
	matrix[i++] = (char *)list->content;
	return (i);
}
static void	create_cmd_args(t_command *var, t_pipex *pipex)
{
	int size;
	int i;

	i = 1;
	size = 1 + ft_lstsize(var->options) + ft_lstsize(var->arguments);
	pipex->cmd_arguments = (char **)malloc_garbage(sizeof(char *) * (size + 1));
	if (!(pipex->cmd_arguments))
		return ;
	pipex->cmd_arguments[size + 1] = NULL;
	pipex->cmd_arguments[0] = var->command;
	if (var->options)
		i = fill_matrix(pipex->cmd_arguments, var->options, i);
	if (var->arguments)
		fill_matrix(pipex->cmd_arguments, var->arguments, i);
}

static void	check_child_dup(t_pipex *pipex, t_command *var)
{
	/* Create a function to check for dup2 with the lines below*/
	// ft_printf("Pass1\n");
	if (var->infile)
		dup2(var->infile_fd, 0);
	else if (pipex->id != 0)
	{
	// ft_printf("Pass1.5\n");
		if (!dup2(pipex->pipefd[2 * pipex->id - 2], 0))
		{
	// ft_printf("Pass1.6\n");
			free_c_process(pipex, var);
	// ft_printf("Pass1.7\n");
			exit (errno);
		}
		pipex->except1 = 2 * pipex->id - 2;
	}
	// ft_printf("Pass2\n");
	if (var->outfile)
		dup2(var->outfile_fd, 1);
	else if (var->next)
	{
	// ft_printf("Pass2.5\n");
		if (!dup2(pipex->pipefd[2 * pipex->id + 1], 1))
		{
			free_c_process(pipex, var);
			exit (errno);
		}
		pipex->except2 = 2 * pipex->id + 1;
	}
}

static void	check_child_fd(t_pipex *pipex, t_command *var)
{
	if (var->infile)
	{
	// ft_printf("Pass5.5\n");
		if (var->infile_fd == -1)
		{
			free_c_process(pipex, var);
			exit (errno);
		}
	}
	// ft_printf("Pass6\n");
	if (var->outfile)
	{
	// ft_printf("Pass6.5\n");
		if (var->outfile_fd == -1)
		{
			free_c_process(pipex, var);
			exit (errno);
		}
	}
}

void	child(t_var *main_process, t_pipex *pipex, t_command *var, char *envp[])
{
	/* Create a function to check for dup2 with the lines below*/
	check_child_dup(pipex, var);
	close_pipes(pipex);
	create_cmd_args(var, pipex);
	pipex->cmd = check_cmd_path(pipex);
	/* Create a function to check FD errors with the lines below*/
	check_child_fd(pipex, var);
	if (check_for_builtin(var))
		selec_ope_pipex(main_process, var);
	else
		execve(pipex->cmd, pipex->cmd_arguments, envp);
	// ft_printf("Pass8\n");
	perror(pipex->cmd);
	free_c_process(pipex, var);
	exit(errno);
}

void	child_single(t_pipex *pipex, t_command *var, char *envp[])
{
	/* Create a function to check for dup2 with the lines below*/
	if (var->infile)
		dup2(var->infile_fd, 0);
	if (var->outfile)
		dup2(var->outfile_fd, 1);
	create_cmd_args(var, pipex);
	pipex->cmd = check_cmd_path(pipex);
	/* Create a function to check FD errors with the lines below*/
	check_child_fd(pipex, var);
	execve(pipex->cmd, pipex->cmd_arguments, envp);
	perror(pipex->cmd);
	free_c_process(pipex, var);
	exit(errno);
}
