/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:16:41 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/02 19:51:35 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	refresh_handler(int sig)
{
	(void)sig;
	ft_putchar('\n');
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_handler(int sig)
{
	int	newfd[2];

	pipe(newfd);
	(void)sig;
	dup2(newfd[0], 0);
	close(newfd[1]);
}