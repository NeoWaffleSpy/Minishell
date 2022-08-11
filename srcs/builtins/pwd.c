/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:41 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/30 18:55:23 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pwd(t_var *var, t_command *comm)
{
	char	*cwd;

	var->exit_status = 0;
	if (comm->arguments && comm->arguments->is_append)
		var->exit_status = call_error("pwd: bad options:",
				comm->arguments->filename, 1);
	if (var->exit_status)
		return ;
	cwd = getcwd(NULL, 0);
	ft_printf_fd(1, "%s\n", cwd);
	free(cwd);
}
