/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 21:32:32 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/05 21:33:49 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	selec_ope_pipex(t_var *main_process, t_command *var, t_pipex *pipex)
{
	dup2(pipex->pipefd[1], 1);
	if (!ft_strcmp(var->command, "cd"))
		cd(main_process, var);
	else if (!ft_strcmp(var->command, "echo"))
		ft_echo(var);
	else if (!ft_strcmp(var->command, "pwd"))
		print_pwd(main_process, var);
	else if (!ft_strcmp(var->command, "export"))
		export_var(main_process, var);
	else if (!ft_strcmp(var->command, "unset"))
		unset_var(main_process, var);
	else if (!ft_strcmp(var->command, "env"))
		ft_print_env(main_process->env, var);
	else if (!ft_strcmp(var->command, "exit"))
		exit_mini(main_process, var);
}

int	check_for_builtin(t_command *var)
{
	if (!ft_strcmp(var->command, "cd")
		&& !ft_strcmp(var->command, "echo") && !ft_strcmp(var->command, "echo")
		&& !ft_strcmp(var->command, "pwd") && !ft_strcmp(var->command, "export")
		&& !ft_strcmp(var->command, "unset") && !ft_strcmp(var->command, "env")
		&& !ft_strcmp(var->command, "exit"))
		return (1);
	return (0);
}
