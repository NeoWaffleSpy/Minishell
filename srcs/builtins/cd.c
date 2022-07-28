/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:04 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/28 16:07:42 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd(t_var *var, t_command *comm)
{
	if (comm->options)
		var->exit_status = call_error("cd:", "invalid options", 2);
	if (1)
		var->exit_status = call_error("cd:", "too many arguments", 1);
	call_todo("cd");
}
