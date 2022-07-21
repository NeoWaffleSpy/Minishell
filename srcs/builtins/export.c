/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/21 23:14:42 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_dist(char *str, char c)
{
	return (ft_strchr(str, c) - str);
}

void	export_var(t_var *var, t_command *comm)
{
	char	*name;
	char	**split;
	char	*attr;
	int		i;
	int		dist;

	i = 0;
	split = ft_split(comm->arguments, ' ');
	while (split[i])
	{
		if (ft_strchr(split[i], '='))
		{
			attr = NULL;
			dist = get_dist(split[i], '=');
			name = ft_substr(split[i], 0, dist);
			if (split[i][dist + 1])
			{
				attr = ft_substr(split[i], dist + 1, get_dist(split[i], '\0'));
				ft_manually_add_one_env(var->env, name, attr);
				free(attr);
			}
			else
				ft_manually_add_one_env(var->env, name, "");
			free(name);
		}
		free(split[i]);
		i++;
	}
	free(split);
}
