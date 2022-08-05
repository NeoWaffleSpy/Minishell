/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 20:11:13 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/05 21:30:03 by atoullel         ###   ########.fr       */
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

void	child(t_var *main_process, t_pipex *pipex, t_command *var, char *envp[])
{
	/* Create a function to check for dup2 with the lines below*/
	int except1;
	int except2;

	except1 = -1;
	except2 = -1;
	if (var->infile)
		dup2(var->infile_fd, 0);
	else if (pipex->id != 0)
	{
		if (!dup2(pipex->pipefd[2 * pipex->id - 2], 0))
		{
			free_c_process(var, except1, except2);
			exit (errno);
		}
		except1 = 2 * pipex->id - 2;
	}
	if (var->outfile)
		dup2(var->outfile_fd, 1);
	else if (var->next)
	{
		if (!dup2(pipex->pipefd[2 * pipex->id + 1], 1))
		{
			free_c_process(var, except1, except2);
			exit (errno);
		}
		except2 = 2 * pipex->id + 1;
	}
	close_pipes(pipex, except1, except2);
	create_cmd_args(var, pipex);
	pipex->cmd = check_cmd_path(pipex);
	/* Create a function to check FD errors with the lines below*/
	if (var->infile)
	{
		if (var->infile_fd == -1)
		{
			free_c_process(var, except1, except2);
			exit (errno);
		}
	}
	if (var->outfile)
	{
		if (var->outfile_fd == -1)
		{
			free_c_process(var, except1, except2);
			exit (errno);
		}
	}
	if (check_for_builtin(var))
		selec_ope_pipex(main_process, var, pipex);
	else
		execve(pipex->cmd, pipex->cmd_arguments, envp);
	perror(pipex->cmd);
	free_c_process(var, except1, except2);
	exit(errno);
}
