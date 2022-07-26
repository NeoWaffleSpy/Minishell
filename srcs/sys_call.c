/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:06:42 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/26 22:36:53 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	call_error(char *error, char *value, int ret)
{
	ft_printf_fd(2, "%s[%sError%s]: ", WHITE, RED, WHITE);
	ft_printf_fd(2, "%s %s%s%s\n", error, YELLOW, value, RESET_COLOR);
	return (ret);
}

void	call_info(char *info, char *value)
{
	ft_printf("%s[%sInfo%s]: ", WHITE, GREEN, WHITE);
	ft_printf("%-20s %s%s%s\n", info, CYAN, value, RESET_COLOR);
}

void	call_todo(char *ft)
{
	ft_printf("%s%sCette fonction n'es pas encore faite :%s",
		CYAN, BLINK, RESET_COLOR);
	ft_printf(" %s%s%s%s\n", RED, BLINK, ft, RESET_COLOR);
}

void	call_destroy(t_var *var, char *prompt)
{
	free_garbage(prompt);
	rl_clear_history();
	ft_free_env(var->env);
	dump_trash();
}

void	free_command(t_command **comma)
{
	t_command	*tmp;
	t_command	*comm;

	comm = *comma;
	while (comm)
	{
		free_garbage(comm->command);
		if (comm->options)
			free_garbage(comm->options);
		if (comm->arguments)
			free_garbage(comm->arguments);
		tmp = comm->next;
		free_garbage(comm);
		comm = tmp;
	}
}
