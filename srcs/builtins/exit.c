/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:12:08 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/30 17:55:30 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str && (*str == '-' || *str == '+'))
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 20 || (i > 19 && (*str == '-' || *str == '+')))
		return (0);
	return (1);
}

static int	ft_lltoi(char *str)
{
	long long	l_val;
	int			is_neg;

	is_neg = FALSE;
	l_val = 0;
	if (!ft_strcmp(str, "-9223372036854775808"))
		return (0);
	if (str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			is_neg = TRUE;
		str++;
	}
	while (str && *str)
	{
		l_val *= 10;
		l_val += (long long)(*str - '0');
		str++;
		if (l_val < 0)
			return (call_error("exit:", "numeric argument required", 2));
	}
	if (is_neg)
		l_val *= -1;
	return ((int)(l_val % 256));
}

void	exit_mini(t_var *var, t_command *comm)
{
	char	*str;

	if (comm == NULL || comm->pidn != 0)
		ft_printf_fd(2, "exit\n");
	var->exit_loop = FALSE;
	if (comm == NULL || !comm->arguments)
		return ;
	if (comm->arguments && comm->arguments->next)
	{
		var->exit_status = call_error("exit:", "too many arguments", 2);
		var->exit_loop = TRUE;
		return ;
	}
	str = comm->arguments->filename;
	if (!is_num(str))
		var->exit_status = call_error("exit:", "numeric argument required", 2);
	else
		var->exit_status = ft_lltoi(str);
}
