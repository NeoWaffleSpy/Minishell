/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:45:07 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/21 23:23:57 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_env_to_char(t_env *env)
{
	char	**tab;
	int		env_size;
	int		i;

	i = 0;
	env_size = ft_env_size(env);
	tab = malloc_garbage(sizeof(char *) * (env_size + 1));
	if (!tab)
		return (NULL);
	ft_bzero(tab, env_size + 1);
	while (env)
	{
		tab[i] = ft_printf_var("%s=%s", env->name, env->content);
		i++;
		env = env->next;
	}
	return (tab);
}

int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	ft_is_valid_env_variable(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == 0)
		return (0);
	if (ft_isdigit(str[0]) == 1)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*ft_find_env_elem(t_env *env_list, char *name)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->name, name) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	ft_manually_add_one_env(t_env *env_list, char *name, char *content)
{
	t_env	*env_set;
	t_env	*env_new;

	if (ft_is_valid_env_variable(name) == 1)
	{
		env_set = ft_find_env_elem(env_list, name);
		if (env_set)
		{
			free_garbage(env_set->content);
			env_set->content = ft_strdup(content);
		}
		else
		{
			env_new = malloc_garbage(sizeof(t_env));
			env_new->name = ft_strdup(name);
			env_new->content = ft_strdup(content);
			env_new->next = NULL;
			ft_env_add_back(&env_list, env_new);
		}
	}
}
