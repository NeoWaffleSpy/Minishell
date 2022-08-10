/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:32:32 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/06 02:21:46 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_cmd_path(t_pipex *pipex, t_command *var)
{
	char	**paths;
	char	*command;
	char	*cmd_path;

	paths = pipex->path_list;
	command = ft_strjoin("/", var->command);
	while (paths && *paths)
	{
		cmd_path = ft_strjoin(*paths, command);
		if (access(cmd_path, 0) == 0)
		{
			pipex->cmd = cmd_path;
			return (cmd_path);
		}
		paths++;
	}
	return (NULL);
}

static int	is_dir(t_var *main_process, t_command *var)
{
	struct stat	path;

	stat(var->command, &path);
	if (S_ISREG(path.st_mode) == 0)
	{
		ft_printf_fd(2, "%s%s\n", var->command, ": Is a directory");
		main_process->exit_status = 126;
		return (1);
	}
	return (0);
}

char	*check_cmd_path(t_var *main_process, t_pipex *pipex, t_command *var)
{
	if (!(var->command[0]))
	{
		pipex->cmd = var->command;
		return (NULL);
	}
	if ((var->command[0] == '.' || var->command[0] == '/')
		&& access(var->command, 0) == 0)
	{
		if (is_dir(main_process, var))
			return (NULL);
		pipex->cmd = var->command;
		return (var->command);
	}
	if (var->command[ft_strlen(var->command) - 1] == '/')
	{
		ft_printf_fd(2, "%s%s\n", var->command, ": Is not a directory");
		main_process->exit_status = 126;
		return (NULL);
	}
	return (find_cmd_path(pipex, var));
}

void	execute_single_builtin(t_var *main_process, t_command *var)
{
	int	stdout_copy;

	stdout_copy = dup(1);
	if (!check_infile_and_outfile(var, var->infile, var->outfile))
	{
		if (var->outfile)
			dup2(var->outfile_fd, 1);
		selec_ope_pipex(main_process, var);
	}
	dup2_close(stdout_copy, 1);
	free_p_process(var);
}
