/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:41 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 19:31:31 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_pwd(t_var *var, t_command *comm)
{
	var->exit_status = 0;
	if (comm->options)
		var->exit_status = call_error("pwd: bad options:", comm->options, 1);
	if (comm->arguments)
		var->exit_status = call_error("pwd: too many arguments", "", 1);
	if (var->exit_status)
		return ;
	ft_printf_fd(comm->outfile, "%s\n",
		ft_find_env_elem(var->env, "PWD")->content);
}
