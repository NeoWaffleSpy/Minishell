/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:59:26 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/10 11:17:57 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nbr))
	{
		if (i != pipex->except1 && i != pipex->except2
			&& pipex->pipefd[i] != -1)
			close(pipex->pipefd[i]);
		i++;
	}
}

void	clean_parent(t_var *main_process, t_pipex *pipex)
{
	int	status;

	close_pipes(pipex);
	while (1)
	{
		pipex->pidn = wait(&status);
		if (pipex->pidn < 0)
			break ;
		main_process->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			main_process->exit_status = 128;
			main_process->exit_status += WTERMSIG(status);
		}
	}
	if (main_process->exit_status >= 128)
		ft_printf("\n");
}

void	free_p_process(t_command *var)
{
	if (var->infile)
	{
		if (var->infile_fd >= 0)
			close(var->infile_fd);
	}
	if (var->outfile)
	{
		if (var->outfile_fd >= 0)
			close(var->outfile_fd);
	}
}

void	free_c_process(t_pipex *pipex, t_command *var)
{
	if ((pipex->except1 >= 0) && (pipex->pipefd[pipex->except1] >= 0))
		close(pipex->pipefd[pipex->except1]);
	if ((pipex->except2 >= 0) && (pipex->pipefd[pipex->except2] >= 0))
		close(pipex->pipefd[pipex->except2]);
	if (var->infile)
	{
		if (var->infile_fd >= 0)
			close(var->infile_fd);
	}
	if (var->outfile)
	{
		if (var->outfile_fd >= 0)
			close(var->outfile_fd);
	}
	dump_trash();
}

void	child_dup_error(t_pipex *pipex, t_command *var)
{
	perror("dup2 error");
	close_pipes(pipex);
	free_c_process(pipex, var);
	exit (errno);
}
