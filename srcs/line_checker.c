/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:03:06 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/23 19:40:08 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	skip_space(char **line)
{
	while (*line && **line && (**line == ' ' || **line == '	'))
		(*line)++;
}

static void	get_command(t_command *comm, char **line)
{
	int	i;

	i = 0;
	skip_space(line);
	while (*line && (*line)[i] && (*line)[i] != ' ' && (*line)[i] != '	')
		i++;
	if (i == 0)
		return ;
	comm->command = ft_substr(*line, 0, i);
	*line += i;
	skip_space(line);
}

static void	get_options(t_command *comm, char **line)
{
	int		i;
	char	*str;

	i = 0;
	while (*line && (*line)[i] && (*line)[i] == '-')
	{
		while (*line && (*line)[i] && (*line)[i] != ' ' && (*line)[i] != '	')
			i++;
		while (*line && (*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '	'))
			i++;
	}
	if (i > 0)
	{
		str = ft_strljoin(comm->options, *line, i);
		if (comm->options)
			free(comm->options);
		comm->options = str;
	}
	*line += i;
}

static void	get_args(t_command *comm, char **line)
{
	int		i;
	char	*str;

	i = 0;
	while (*line && (*line)[i] && (*line)[i] != '-')
	{
		if (*line && (*line)[i] == '\"')
			while (*line && (*line)[++i] == '\"')
				continue ;
		if (*line && (*line)[i] == '\'')
			while (*line && (*line)[++i] == '\'')
				continue ;
		while (*line && (*line)[i] && (*line)[i] != ' ' && (*line)[i] != '	')
			i++;
		while (*line && (*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '	'))
			i++;
	}
	if (i > 0)
	{
		str = ft_strljoin(comm->arguments, *line, i);
		if (comm->arguments)
			free(comm->arguments);
		comm->arguments = str;
	}
	*line += i;
}

t_command	*fill_command(char *line)
{
	t_command	*comm;
	int			i;

	i = 0;
	comm = init_comm();
	get_command(comm, &line);
	if (comm->command == NULL)
		return (comm);
	while (*line && *line != '|')
	{
		if (*line == '-')
			get_options(comm, &line);
		else
			get_args(comm, &line);
	}
	clean_str(&comm->command);
	clean_str(&comm->options);
	clean_str(&comm->arguments);
	if (*line == '|')
		comm->next = fill_command(line);
	return (comm);
}
