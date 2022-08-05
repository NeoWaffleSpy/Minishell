/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:00:23 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/05 16:19:12 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_double_array(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free_garbage(str[i]);
		i++;
	}
	free_garbage(str);
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
	free_garbage(env->name);
	env->name = NULL;
	free_garbage(env->content);
	env->content = NULL;
	free_garbage(env);
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
		return (call_error("env: Too many options", "", 1));
	if (comm->arguments)
		return (call_error("env: Too many arguments", "", 1));
	while (env_list)
	{
		if (env_list->content)
		{
			ft_printf_fd(1, "%s=", env_list->name);
			ft_printf_fd(1, "%s\n", env_list->content);
		}
		env_list = env_list->next;
	}
	return (0);
}
