/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:36:25 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/09 16:56:47 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_quotes(char *line, t_var *var)
{
	var->quotes = 0;
	var->dquotes = 0;
	while (line && *line)
	{
		if (!(var->quotes % 2) && *line == '\"')
			var->dquotes++;
		if (!(var->dquotes % 2) && *line == '\'')
			var->quotes++;
		line++;
	}
}

void	sigint_handler(int	*return_value)
{
	static int	*value;

	if (return_value)
		value = return_value;
	else
		*value = 130;
}

static int	loop_heredoc(t_var *var, t_file *delim, int wr_fd)
{
	char	*line;

	line = readline("heredoc> ");
	if (!line)
	{
		if (var->exit_status != 130)
			call_info("Heredoc ended with", "EOF");
		return (1);
	}
	add_garbage(line);
	if (!ft_strcmp(line, delim->filename))
	{
		free_garbage(line);
		return (1);
	}
	if (delim->is_append != 2)
		replace_dollar(var, &line, TRUE);
	write(wr_fd, line, ft_strlen(line));
	write(wr_fd, "\n", 1);
	free_garbage(line);
	return (0);
}

static int	get_here_id(void)
{
	static int	here_id;

	if (!here_id)
		here_id = 1;
	else
		here_id++;
	if (here_id > 10000)
		here_id = 1;
	return (here_id);
}

t_file	*create_heredoc(t_var *var, t_file *delim)
{
	int		here_id;
	int		wr_fd;
	int		stdin_copy;
	char	*filename;

	here_id = get_here_id();
	init_heredoc(&var->exit_status, &stdin_copy);
	filename = ft_printf_var("/tmp/.heredoc_%d", here_id);
	if (ft_strchr(delim->filename, '\'') || ft_strchr(delim->filename, '\"'))
		delim->is_append = 2;
	delim->filename = clean_str(delim->filename);
	wr_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (!loop_heredoc(var, delim, wr_fd))
		continue ;
	close(wr_fd);
	free_garbage(delim->filename);
	delim->filename = filename;
	if (var->exit_status == 130)
		dup2_close(stdin_copy, STDIN_FILENO);
	else
		close(stdin_copy);
	if (var->exit_status == 130)
		ft_printf("\n");
	init_signal2();
	return (delim);
}
