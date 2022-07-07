/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_call.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:06:42 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/07 16:42:41 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	call_error(char *error, char *value)
{
	printf("%s[%sError%s]: ", WHITE, RED, WHITE);
	printf("%s %s%s%s\n", error, YELLOW, value, RESET_COLOR);
	return(1);
}

void	call_info(char *info, char *value)
{
	printf("%s[%sInfo%s]: ", WHITE, GREEN, WHITE);
	printf("%-20s %s%s%s\n", info, CYAN, value, RESET_COLOR);
}
