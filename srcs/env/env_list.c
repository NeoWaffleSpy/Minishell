/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:44:49 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/17 18:42:18 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_env_last(t_env *env)
{
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (env);
}

void	ft_env_add_back(t_env **env_start, t_env *new)
{
	t_env	*last;

	if (*env_start == NULL)
	{
		*env_start = new;
		return ;
	}
	else
	{
		last = ft_env_last(*env_start);
		last->next = new;
	}
}

char	*ft_env_get_content(t_env *env_list, char *name, char *env_line,
		int flag_plus)
{
	t_env	*old_env;
	char	*joined;

	if (!env_line)
		return (NULL);
	if (flag_plus == 0)
		return (ft_strdup(env_line));
	else
	{
		old_env = ft_find_env_elem(env_list, name);
		if (old_env == NULL)
			return (ft_strdup(env_line));
		else
		{
			joined = ft_strjoin(old_env->content, env_line);
			free(old_env->content);
			return (joined);
		}
	}
}

t_env	*ft_get_env_element(t_env *env_list, char *env_line)
{
	int			i;
	int			flag_plus;
	t_env		*tmp_element;

	i = 0;
	flag_plus = 0;
	tmp_element = malloc(sizeof(*tmp_element));
	while (env_line[i] && env_line[i] != '=')
	{
		if (env_line[i] == '+' && env_line[i + 1] == '=')
			flag_plus = 1;
		i++;
	}
	tmp_element->name = ft_substr(env_line, 0, i - flag_plus);
	if (env_line[i] == '=')
	{
		i++;
		tmp_element->content = ft_env_get_content(env_list, tmp_element->name,
				&env_line[i], flag_plus);
	}
	else
		tmp_element->content = NULL;
	tmp_element->next = NULL;
	return (tmp_element);
}

t_env	*ft_env_to_list(char **env)
{
	t_env	*env_start;
	t_env	*tmp_element;

	env_start = NULL;
	while (*env)
	{
		tmp_element = ft_get_env_element(env_start, *env);
		ft_env_add_back(&env_start, tmp_element);
		env++;
	}
	return (env_start);
}
