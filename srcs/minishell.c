/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:46:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/17 20:56:08 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*create_prompt(char *prompt, char *cwd)
{
	char	*c_dir;
	int		i;

	i = ft_strlen(cwd) - 1;
	c_dir = &(cwd[i]);
	while (cwd[--i] != '/')
		c_dir = &(cwd[i]);
	if (prompt)
		free(prompt);
	prompt = ft_printf_var("👹 %s21m%s%s%s%s %s➜%s ",
			BASE, BOLD, BLUE, c_dir, RESET_COLOR, CYAN, RESET_COLOR);
	return (prompt);
}

static void	read_command(char *prompt, t_env *env)
{
	t_var	var;
	char	*line;

	var.exit_loop = TRUE;
	var.current_dir = getcwd(NULL, 0);
	var.env = env;
	while (var.exit_loop)
	{
		var.quotes = 0;
		var.dquotes = 0;
		if (line)
			free(line);
		prompt = create_prompt(prompt, var.current_dir);
		line = readline(prompt);
		count_quotes(line, &var);
		if (line && *line)
			add_history(line);
		if (var.quotes % 2 || var.dquotes % 2)
			call_error("Unable to handle unclosed quotes:", line);
		else if (selector(&var, line))
			call_error("Command not recognized:", line);
	}
	call_destroy(&var, prompt);
}

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = ft_env_to_list(env);
	prompt = NULL;
	read_command(prompt, env_list);
	free(prompt);
	ft_free_env(env_list);
	return (0);
}
