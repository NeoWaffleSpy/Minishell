/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:46:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 20:31:51 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_prompt(char *prompt, t_env *env)
{
	char	*c_dir;
	char	*cwd;
	int		i;

	cwd = ft_find_env_elem(env, "PWD")->content;
	i = ft_strlen(cwd);
	while (i >= 0 && cwd[--i] != '/')
		c_dir = &(cwd[i]);
	if (prompt)
		free(prompt);
	prompt = ft_printf_var(
			"\001👹\002 \001%s21m%s%s\002%s\001%s\002 \001%s\002➜\001%s\002 ",
			BASE, BOLD, BLUE, c_dir, RESET_COLOR, CYAN, RESET_COLOR);
	return (prompt);
}

static void	reset_values(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	read_command(char *prompt, t_env *env)
{
	t_var	var;
	char	*line;

	var.exit_loop = TRUE;
	var.env = env;
	while (var.exit_loop)
	{
		reset_var(&var);
		prompt = create_prompt(prompt, var.env);
		line = readline(prompt);
		if (!line)
			continue ;
		if (line && *line)
			add_history(line);
		replace_dollar(&var, &line);
		count_quotes(line, &var);
		if (var.quotes % 2 || var.dquotes % 2)
			call_error("Unable to handle unclosed quotes:", line);
		else if (*line != '\0')
			selector(&var, line);
		free(line);
	}
	ft_printf("exit\n");
	call_destroy(&var, prompt);
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_env	*env_list;

	(void)ac;
	(void)av;
	(void)reset_values;
	env_list = ft_env_to_list(env);
	prompt = NULL;
	read_command(prompt, env_list);
	free(prompt);
	ft_free_env(env_list);
	return (0);
}
