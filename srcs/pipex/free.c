/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:59:26 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/06 02:04:53 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nbr))
	{
		if (pipex->pipefd[i] != pipex->except1 && pipex->pipefd[i] != pipex->except2)
			close(pipex->pipefd[i]);
		i++;
	}
}

void	free_p_process(t_command *var)
{
	if (var->infile)
	{
		if (var->infile_fd)
			close(var->infile_fd);
	}
	if (var->outfile)
	{
		if (var->outfile_fd)
			close(var->outfile_fd);
	}
}

void	free_c_process(t_pipex *pipex, t_command *var)
{
	if (pipex->except1)
		close(pipex->except1);
	if (pipex->except2)
		close(pipex->except2);
	if (var->infile)
	{
		if (var->infile_fd)
			close(var->infile_fd);
	}
	if (var->outfile)
	{
		if (var->outfile_fd)
			close(var->outfile_fd);
	}
	dump_trash();
}
