/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:41:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/30 22:21:13 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*init_comm(void)
{
	t_command	*comm;

	comm = malloc_garbage(sizeof(t_command));
	comm->command = NULL;
	comm->options = NULL;
	comm->arguments = NULL;
	comm->next = NULL;
	comm->infile = NULL;
	comm->outfile = NULL;
	comm->infile_fd = 0;
	comm->outfile_fd = 1;
	comm->error = 0;
	comm->delim = NULL;
	comm->do_expand = 1;
	return (comm);
}

void	init_var(t_var *var, t_env *env)
{
	var->exit_loop = TRUE;
	var->env = env;
	var->exit_status = 0;
}

void	reset_var(t_var *var)
{
	var->quotes = 0;
	var->dquotes = 0;
}

void	init_signal(void)
{
	signal(SIGINT, refresh_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_child(void)
{
	signal(SIGINT, SIG_IGN);
}
