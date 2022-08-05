/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:54:41 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/05 21:35:32 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_cmdlstsize(t_command *lst)
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

static	void	find_env_path(t_pipex *pipex, char *envp[])
{
	if (!(*envp))
	{
		pipex->env_paths = NULL;
		return ;
	}
	while ((ft_strncmp(*envp, "PATH", 4) != 0) && *envp)
		envp++;
	pipex->env_paths = *envp + 5;
}

static	void	clean_parent(t_var *main_process, t_pipex *pipex, t_command *var)
{
	int	status;

	close_pipes(pipex, -1, -1);
	while (1)
	{
		pipex->pidn = wait(&status);
		if (pipex->pidn < 0)
			break ;
		main_process->exit_status = WEXITSTATUS(status);
	}
	free_p_process(var);
}

static void	creat_pipes(t_pipex *pipex, t_var *main_process, t_command *var)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipefd + 2 * i) != 0)
			clean_parent(main_process, pipex, var);
		i++;
	}
}

static void	iterate_child(t_var *main_process, t_pipex *pipex, t_command *var, char *envp[])
{
	int	file_err;

	while ((pipex->id)++ < pipex->cmd_nbr)
	{
		file_err = 0;
		if (var->infile)
		{
			var->infile_fd = open(var->infile->filename, O_RDONLY);
			if (access(var->infile->filename, R_OK))
			{
				perror(var->infile->filename);
				file_err = 1;
			}
		}
		if (var->outfile)
		{
			if (var->outfile->is_append)
				var->outfile_fd = open(var->outfile->filename, O_APPEND
						|O_CREAT | O_RDWR, 0000644);
			else
				var->outfile_fd = open(var->outfile->filename, O_TRUNC
						| O_CREAT | O_RDWR, 0000644);
			if (file_err && access(var->outfile->filename, W_OK))
				perror(var->outfile->filename);
		}
		pipex->pidn = fork();
		if (pipex->pidn == 0)
			child(main_process, pipex, var, envp);
		var = var->next;
	}
}

int	pipex(t_var *main_process, t_command *var, char *envp[])
{
	t_pipex	pipex;
	int		stdout_copy;

	stdout_copy = dup(1);
	pipex.cmd_nbr = ft_cmdlstsize(var);
	ft_printf("\n\n\n%d\n\n\n", pipex.cmd_nbr);
	pipex.pipe_nbr = 2 * (pipex.cmd_nbr - 1);
	pipex.pipefd = (int *)malloc_garbage(sizeof(int) * pipex.pipe_nbr);
	if (!pipex.pipefd)
		err_message(1, "Pipe malloc err\n");
	find_env_path(&pipex, envp);
	pipex.path_list = ft_split(pipex.env_paths, ':');
	creat_pipes(&pipex, main_process, var);
	if (check_for_builtin(var))
	{
		selec_ope_pipex(main_process, var, &pipex);
		pipex.id = 1;
		var = var->next;
	}
	else
		pipex.id = 0;
	dup2_close(stdout_copy, 1);
	iterate_child(main_process, &pipex, var, envp);
	clean_parent(main_process, &pipex, var);
	return (0);
}
