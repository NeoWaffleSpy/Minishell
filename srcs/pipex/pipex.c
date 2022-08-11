/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:54:41 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/11 03:25:20 by atoullel         ###   ########.fr       */
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

static void	create_pipes(t_pipex *pipex, char *envp[])
{
	int	i;

	i = 0;
	while (i < pipex->pipe_nbr)
		pipex->pipefd[i++] = -1;
	i = 0;
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipefd + (2 * i)) != 0)
		{
			close_pipes(pipex);
			ft_free_double_array(envp);
			err_message(2, "Pipe creation err\n");
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
		var->pidn = pipex->pidn;
		var = var->next;
		(pipex->id)++;
	}
}

void	exec_single_command(t_var *main_process, t_pipex *pipex, t_command *var,
	char *envp[])
{
	int	status;

	var->pidn = 1;
	find_env_path(pipex, envp);
	pipex->path_list = ft_split(pipex->env_paths, ':');
	if (!var->command)
		no_cmd(var);
	else if (check_for_builtin(var))
		execute_single_builtin(main_process, var);
	else if (check_cmd_path(main_process, pipex, var))
	{
		pipex->pidn = fork();
		if (pipex->pidn == 0)
			child_single(pipex, var, envp);
		pipex->pidn = wait(&status);
		main_process->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			main_process->exit_status = 128 + WTERMSIG(status);
		if (main_process->exit_status == 131)
			ft_printf("Quit (core dumped)");
		if (main_process->exit_status >= 128)
			printf("\n");
	}
	else
		err_cmd_not_found(main_process, var);
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
			err_message(2, "Pipe malloc err\n");
		find_env_path(&pipex, envp);
		pipex.path_list = ft_split(pipex.env_paths, ':');
		create_pipes(&pipex, envp);
		iterate_child(main_process, &pipex, var, envp);
		clean_parent(main_process, &pipex, var);
	}
	ft_free_double_array(envp);
	return (0);
}
