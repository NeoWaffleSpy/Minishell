/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 17:12:08 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/26 22:43:28 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str && str[i] == '-')
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 20 || (i > 19 && str[0] != '-'))
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
	if (str && *str == '-')
	{
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

static void	free_split(char **split, char *str)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		free_garbage(split[i]);
		i++;
	}
	free_garbage(split);
	free_garbage(str);
}

void	exit_mini(t_var *var, t_command *comm)
{
	char	*str;
	char	**split;

	ft_printf("exit\n");
	var->exit_loop = FALSE;
	if (comm == NULL)
		return ;
	str = ft_str_sp_join(comm->options, comm->arguments);
	if (!str)
		return ;
	split = ft_split(str, ' ');
	if (split && !is_num(*split))
		var->exit_status = call_error("exit:", "numeric argument required", 2);
	else if (split && *(split + 1))
	{
		var->exit_status = call_error("exit:", "too many arguments", 2);
		var->exit_loop = TRUE;
	}
	else if (split)
		var->exit_status = ft_lltoi(*split);
	free_split(split, str);
}
