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

static char	*find_cmd_path(char **paths, char *command, char *cmd_path)
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

char	*check_cmd_path(t_pipex *pipex, t_command *var)
{
	char	**paths;
	char	*command;
	char	*cmd_path;

	if (!(pipex->cmd_arguments) || !(pipex->cmd_arguments[0])
		|| !(var->command[0]))
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

void	execute_single_builtin(t_var *main_process, t_command *var)
{
	int	stdout_copy;

	stdout_copy = dup(1);

	if (var->outfile)
		dup2(var->outfile_fd, 1);
	selec_ope_pipex(main_process, var);
	dup2_close(stdout_copy, 1);
}
