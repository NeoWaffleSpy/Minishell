/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:41:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 19:48:18 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*init_comm(void)
{
	t_command	*comm;

	comm = malloc(sizeof(t_command));
	comm->command = NULL;
	comm->options = NULL;
	comm->arguments = NULL;
	comm->next = NULL;
	comm->infile = 0;
	comm->outfile = 1;
	return (comm);
}

void	reset_var(t_var *var)
{
	var->quotes = 0;
	var->dquotes = 0;
	var->exit_status = 0;
}
