/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 23:59:26 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/11 12:53:49 by atoullel         ###   ########.fr       */
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

static void	sig_check(t_var *main_process, t_command *var)
{
	if (main_process->exit_status == 127)
		ft_printf_fd(2, "%s%s\n", var->command, ": command not found");
	if (main_process->exit_status == 126)
		ft_printf_fd(2, "%s%s\n", var->command, ": Is a directory");
	if (main_process->exit_status == 50)
	{
		main_process->exit_status = 126;
		ft_printf_fd(2, "%s%s\n", var->command, ": Is not a directory");
	}
}

void	clean_parent(t_var *main_process, t_pipex *pipex, t_command *var)
{
	int	status;
	int	boolean;

	boolean = FALSE;
	close_pipes(pipex);
	while (var)
	{
		waitpid(var->pidn, &status, 0);
		main_process->exit_status = WEXITSTATUS(status);
		sig_check(main_process, var);
		if (WIFSIGNALED(status))
			main_process->exit_status = 128 + WTERMSIG(status);
		if (main_process->exit_status >= 128
			&& main_process->exit_status != 141)
			boolean = TRUE;
		var = var->next;
	}
	if (main_process->exit_status == 131)
		ft_printf("Quit (core dumped)");
	if (boolean)
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
