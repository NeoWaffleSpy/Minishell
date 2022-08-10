/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 13:00:53 by atoullel          #+#    #+#             */
/*   Updated: 2022/08/10 17:50:54 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	err_message(int fd, char *msg)
{
	write(fd, msg, ft_strlen(msg));
	exit(1);
}

void	err_cmd_not_found(t_var *main_process, t_command *var)
{
	ft_printf_fd(2, "%s%s\n", var->command, ": command not found");
	main_process->exit_status = 127;
}
