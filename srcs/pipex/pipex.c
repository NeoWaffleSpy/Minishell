/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:54:41 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/10 01:24:26 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void	find_env_path(t_pipex *pipex, char *envp[])
{
	if (!envp || !(*envp))
	{
		pipex->env_paths = NULL;
		return ;
	}
	while (*envp && (ft_strncmp(*envp, "PATH", 4) != 0))
		envp++;
	if (*envp && ft_strncmp(*envp, "PATH", 4) == 0)
		pipex->env_paths = *envp + 5;
	else
		pipex->env_paths = NULL;
}

static void	create_pipes(t_var *main_process, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipefd + (2 * i)) != 0)
		{
			perror("pipe creation");
			clean_parent(main_process, pipex);// how to properly close pipes if one fails.
			exit (1);
		}
		i++;
	}
}

static void	iterate_child(t_var *main_process, t_pipex *pipex, t_command *var,
	char *envp[])
{
	pipex->id = 0;
	while ((pipex->id) < pipex->cmd_nbr)
	{
		pipex->pidn = fork();
		if (pipex->pidn == 0)
			child(main_process, pipex, var, envp);
		var = var->next;
		(pipex->id)++;
	}
}

void	exec_single_command(t_var *main_process, t_pipex *pipex, t_command *var,
	char *envp[])
{
	int	status;

	find_env_path(pipex, envp);
	pipex->path_list = ft_split(pipex->env_paths, ':');
	if (check_for_builtin(var))
	{
		if (!check_infile_and_outfile(var, var->infile, var->outfile))
			execute_single_builtin(main_process, var);
		free_p_process(var);
	}
	else
	{
		pipex->pidn = fork();
		if (pipex->pidn == 0)
			child_single(pipex, var, envp);
		pipex->pidn = wait(&status);
		main_process->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			main_process->exit_status = 128;
			main_process->exit_status += WTERMSIG(status);
		}
	}
}

int	pipex(t_var *main_process, t_command *var, char *envp[])
{
	t_pipex	pipex;

	pipex.cmd_nbr = ft_cmdlstsize(var);
	pipex.except1 = -1;
	pipex.except2 = -1;
	if (pipex.cmd_nbr < 2)
		exec_single_command(main_process, &pipex, var, envp);
	else
	{
		pipex.pipe_nbr = 2 * (pipex.cmd_nbr - 1);
		pipex.pipefd = (int *)malloc_garbage(sizeof(int) * pipex.pipe_nbr);
		if (!pipex.pipefd)
			err_message(1, "Pipe malloc err\n");
		find_env_path(&pipex, envp);
		pipex.path_list = ft_split(pipex.env_paths, ':');
		create_pipes(main_process, &pipex);
		iterate_child(main_process, &pipex, var, envp);
		clean_parent(main_process, &pipex);
	}
	ft_free_double_array(envp);
	return (0);
}
