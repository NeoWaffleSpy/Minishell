/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:46:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/12 20:16:02 by ncaba            ###   ########.fr       */
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

static void	read_command(char *prompt)
{
	t_var	var;
	char	*line;

	var.exit_loop = TRUE;
	var.current_dir = getcwd(NULL, 0);
	while (var.exit_loop)
	{
		prompt = create_prompt(prompt, var.current_dir);
		line = readline(prompt);
		if (line && *line)
			add_history(line);
		if (selector(&var, line))
			call_error("Command not recognized:", line);
		free(line);
	}
	call_destroy(&var, prompt);
}

int	main(void)
{
	char	*prompt;

	prompt = NULL;
	read_command(prompt);
	free(prompt);
	return (0);
}
