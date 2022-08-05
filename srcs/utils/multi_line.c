/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:36:25 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/05 13:45:33 by ncaba            ###   ########.fr       */
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

int	dup2_close(int oldfd, int newfd)
{
	if (oldfd != newfd)
	{
		if (dup2(oldfd, newfd) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror("pipe");
			return (0);
		}
		close(oldfd);
	}
	return (1);
}

void	create_heredoc(t_var *var, t_file *delim)
{
	int		wr_fd;
	char	*line;
	int		stdin_copy;

	init_heredoc(&var->exit_status);
	stdin_copy = dup(0);
	wr_fd = open("/tmp/.heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	line = NULL;
	while (1)
	{
		if (line)
			free_garbage(line);
		line = readline("heredoc> ");
		if (!line)
		{
			if (var->exit_status != 130)
				call_info("Heredoc ended with", "EOF");
			break ;
		}
		add_garbage(line);
		if (!ft_strcmp(line, delim->filename))
			break ;
		if (delim->is_append != 2)
			replace_dollar(var, &line, TRUE);
		write(wr_fd, line, ft_strlen(line));
		write(wr_fd, "\n", 1);
	}
	if (line)
		free_garbage(line);
	close(wr_fd);
	free_garbage(delim->filename);
	delim->filename = ft_strdup("/tmp/.heredoc");
	if (var->exit_status == 130)
	{
		dup2_close(stdin_copy, STDIN_FILENO);
	}
	init_signal();
}
