/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:36:25 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/31 00:23:55 by ncaba            ###   ########.fr       */
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

char	*multiline_quotes(char *line, t_var *var)
{
	char	*newline;
	char	*tmp;

	ft_printf("Prototype function, do not use !\n");
	return (NULL);
	while (var->quotes % 2 || var->dquotes % 2)
	{
		if (var->quotes % 2)
			newline = readline("quote> ");
		else if (var->dquotes % 2)
			newline = readline("dquote> ");
		count_quotes(newline, var);
		tmp = ft_str_sp_join(line, newline);
		free_garbage(line);
		free_garbage(newline);
		line = tmp;
	}
	var->quotes = 0;
	var->dquotes = 0;
	return (tmp);
}

void	create_heredoc(t_command *comm)
{
	int		wr_fd;
	char	*line;

	wr_fd = open("/tmp/.heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	line = NULL;
	while (!line || ft_strcmp(line, comm->delim))
	{
		if (line)
			free_garbage(line);
		line = readline("heredoc> ");
		add_garbage(line);
		write(wr_fd, line, ft_strlen(line));
		write(wr_fd, "\n", 1);
	}
	free_garbage(line);
	close(wr_fd);
	comm->infile_fd = open("/tmp/.heredoc", O_RDONLY);
}
