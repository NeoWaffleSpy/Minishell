/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 03:39:29 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/11 05:55:19 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	err_cmd_not_found2(t_command *var,
	t_pipex *pipex, int err)
{
	free_c_process(pipex, var);
	exit (err);
}

static void	find_cmd_path2(t_pipex *pipex, t_command *var)
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
			return ;
		}
		paths++;
	}
	err_cmd_not_found2(var, pipex, 127);
}

static void	is_dir2(t_command *var, t_pipex *pipex)
{
	struct stat	path;

	stat(var->command, &path);
	if (S_ISREG(path.st_mode) == 0)
		err_cmd_not_found2(var, pipex, 126);
}

void	check_cmd_path2(t_pipex *pipex, t_command *var)
{
	if (!(var->command[0]))
		err_cmd_not_found2(var, pipex, 127);
	if ((var->command[0] == '.' || var->command[0] == '/')
		&& access(var->command, 0) == 0)
	{
		is_dir2(var, pipex);
		pipex->cmd = var->command;
		return ;
	}
	if (var->command[ft_strlen(var->command) - 1] == '/')
		err_cmd_not_found2(var, pipex, 50);
	find_cmd_path2(pipex, var);
}

void	no_cmd(t_command *var)
{
	t_file	*tmp;

	tmp = var->outfile;
	while (tmp)
	{
		close(open(tmp->filename, O_APPEND
				|O_CREAT | O_RDWR, 0000644));
		tmp = tmp->next;
	}
}
