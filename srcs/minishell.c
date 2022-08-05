/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:46:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/05 13:44:38 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_prompt(char *prompt)
{
	char	*c_dir;
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd);
	while (i > 1 && i >= 0 && cwd[--i] != '/')
		c_dir = &(cwd[i]);
	if (i == 1)
		c_dir = cwd;
	if (prompt)
		free_garbage(prompt);
	prompt = ft_printf_var(
			"\001👹\002 \001%s21m%s%s\002%s\001%s\002 \001%s\002➜\001%s\002 ",
			BASE, BOLD, BLUE, c_dir, RESET_COLOR, CYAN, RESET_COLOR);
	free(cwd);
	return (prompt);
}

static int	read_command(char *prompt, t_env *env, char **envp)
{
	t_var	var;
	char	*line;

	init_var(&var, env);
	while (var.exit_loop)
	{
		reset_var(&var);
		prompt = create_prompt(prompt);
		line = readline(prompt);
		if (!line)
			exit_mini(&var, NULL);
		add_garbage(line);
		if (line && *line)
			add_history(line);
		replace_dollar(&var, &line, FALSE);
		count_quotes(line, &var);
		var.exit_status = 0;
		if (var.quotes % 2 || var.dquotes % 2)
			call_error("Unable to handle unclosed quotes:", line, 1);
		else if (line && *line != '\0')
			selector(&var, line, envp);
		free_garbage(line);
	}
	call_destroy(&var, prompt);
	return (var.exit_status);
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_env	*env_list;

	(void)ac;
	(void)av;
	g_garbage = NULL;
	env_list = ft_env_to_list(env);
	prompt = NULL;
	init_signal();
	return (read_command(prompt, env_list, env));
}
