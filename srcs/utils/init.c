/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:41:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/09 16:20:48 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*init_comm(void)
{
	t_command	*comm;

	comm = malloc_garbage(sizeof(t_command));
	comm->command = NULL;
	comm->arguments = NULL;
	comm->next = NULL;
	comm->infile = NULL;
	comm->outfile = NULL;
	comm->infile_fd = 0;
	comm->outfile_fd = 1;
	comm->is_unaccess = FALSE;
	comm->error = 0;
	comm->delim = NULL;
	return (comm);
}

void	init_var(t_var *var, t_env *env)
{
	var->exit_loop = TRUE;
	var->env = env;
	var->exit_status = 0;
}

void	init_signal(void)
{
	signal(SIGINT, refresh_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal2(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	init_heredoc(int *return_value)
{
	sigint_handler(return_value);
	signal(SIGINT, heredoc_handler);
}
