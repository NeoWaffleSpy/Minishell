/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:59:26 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/05 17:50:37 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *pipex, int except1, int except2)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nbr))
	{
		if (pipex->pipefd[i] != except1 && pipex->pipefd[i] != except2)
			close(pipex->pipefd[i]);
		i++;
	}
}

void	free_p_process(t_command var)
{
	if (var->infile_fd)
		close(var->infile_fd);
	if (var->outfile_fd)
		close(var->outfile_fd);
}

void	free_c_process(t_command *var, int fd1, int fd2)
{
	if (fd1)
		close(fd1);
	if (fd2)
		close(fd2);
	if (var->infile_fd)
		close(var->infile_fd);
	if (var->outfile_fd)
		close(var->outfile_fd);
	dump_trash();
}
