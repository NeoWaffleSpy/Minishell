/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:00:23 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 19:03:21 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_double_array(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_cleanly_delone_env(t_env **env_start, t_env *target)
{
	t_env	*env_list;
	t_env	*env_prev;

	env_list = *env_start;
	env_prev = *env_start;
	while (env_list && target)
	{
		if (env_list == target)
		{
			if (env_list == *env_start)
				*env_start = env_list->next;
			else if (env_list->next)
				env_prev->next = env_list->next;
			else if (env_list->next == NULL)
				env_prev->next = NULL;
			ft_delone_env(env_list);
			return ;
		}
		else
			env_prev = env_list;
		env_list = env_list->next;
	}
}

void	ft_delone_env(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	env->name = NULL;
	free(env->content);
	env->content = NULL;
	free(env);
}

void	ft_free_env(t_env *env_start)
{
	t_env	*tmp;

	while (env_start)
	{
		tmp = env_start;
		env_start = env_start->next;
		ft_delone_env(tmp);
	}
}

int	ft_print_env(t_env *env_list, t_command *comm)
{
	if (comm->options)
		return (call_error("env: Too many options", ""));
	if (comm->arguments)
		return (call_error("env: Too many arguments", ""));
	while (env_list)
	{
		if (env_list->content)
		{
			ft_printf_fd(comm->outfile, "%s=", env_list->name);
			ft_printf_fd(comm->outfile, "%s\n", env_list->content);
		}
		env_list = env_list->next;
	}
	return (0);
}
