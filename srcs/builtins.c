/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:02:55 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/12 22:54:46 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	selec_ope(t_var *var, t_command *comm)
{
	if (!ft_strcmp(comm->command, "cd"))
		;
	else if (!ft_strcmp(comm->command, "echo"))
		;
	else if (!ft_strcmp(comm->command, "pwd"))
		;
	else if (!ft_strcmp(comm->command, "export"))
		;
	else if (!ft_strcmp(comm->command, "unset"))
		;
	else if (!ft_strcmp(comm->command, "env"))
		;
	else if (!ft_strcmp(comm->command, "exit"))
		var->exit_loop = FALSE;
	else
		return (1);
	return (0);
}

int	selector(t_var *var, char *operation)
{
	t_command	comm;

	fill_command(&comm, operation);
	selec_ope(var, &comm);
	free_command(&comm);
	if (var->exit_loop == FALSE)
		return (1);
	return (0);
}
