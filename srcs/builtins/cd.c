/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:52:04 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/30 20:15:25 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_check_pwd(t_env *env, char *path, t_env *env_pwd, char *name)
{
	if (env_pwd == NULL)
		ft_manually_add_one_env(env, name, path);
	else
	{
		free_garbage(env_pwd->content);
		env_pwd->content = path;
	}
}

static int	loop_home(t_var *var, char *name, char *msg)
{
	t_env	*env;
	int		i;

	env = ft_find_env_elem(var->env, name);
	if (env != NULL)
	{
		if (*name == 'O')
			ft_printf_fd(1, "%s\n", env->content);
		i = chdir(env->content);
		if (i == -1)
			return (-2);
		return (i);
	}
	var->exit_status = call_error("cd:", msg, 1);
	return (1);
}

static int	home_check(t_var *var, t_command *comm)
{
	if (!comm->arguments || !ft_strcmp(comm->arguments->filename, "--"))
		return (loop_home(var, "HOME", "HOME not set"));
	else if (comm->arguments && !ft_strcmp(comm->arguments->filename, "-"))
		return (loop_home(var, "OLDPWD", "OLDPWD not set"));
	else
		return (chdir(comm->arguments->filename));
}

static void	change_env(t_var *var)
{
	char	*pwd;

	if (ft_find_env_elem(var->env, "PWD"))
	{
		pwd = ft_strdup(ft_find_env_elem(var->env, "PWD")->content);
		ft_check_pwd(var->env, pwd,
			ft_find_env_elem(var->env, "OLDPWD"), "OLDPWD");
		pwd = getcwd(NULL, 0);
		add_garbage(pwd);
		ft_check_pwd(var->env, pwd, ft_find_env_elem(var->env, "PWD"), "PWD");
	}
	else
		ft_cleanly_delone_env(&var->env, ft_find_env_elem(var->env, "OLDPWD"));
}

void	cd(t_var *var, t_command *comm)
{
	int		success;

	success = 0;
	if (comm->arguments && ft_strcmp(comm->arguments->filename, "-")
		&& ft_strcmp(comm->arguments->filename, "--")
		&& comm->arguments->is_append)
		var->exit_status = call_error("cd:", "invalid options", 1);
	else if (comm->arguments && comm->arguments->next)
		var->exit_status = call_error("cd:", "too many arguments", 1);
	else
	{
		success = home_check(var, comm);
		if (success == 0)
			change_env(var);
		else if (success == -1)
			var->exit_status = call_error("cd:", "No such file/directory", 1);
	}
}
