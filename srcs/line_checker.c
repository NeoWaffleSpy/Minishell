/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:03:06 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/12 22:57:57 by ncaba            ###   ########.fr       */
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
	while (*line && *line[i] && (*line[i] != ' ' || *line[i] != '	'))
		i++;
	comm->command = ft_substr(*line, 0, i);
	*line += i;
	skip_space(line);
}

static void	get_options(t_command *comm, char **line)
{
	int	i;

	i = 0;
	while (*line && *line[i] && **line == '-')
	{
		while (*line && *line[i] && (*line[i] != ' ' || *line[i] != '	'))
			i++;
		skip_space(line);
	}
	if (i > 0)
		comm->options = ft_substr(*line, 0, i);
	else
		comm->options = NULL;
}

static void	get_args(t_command *comm, char **line)
{
	int	i;

	i = 0;
	while (*line && *line[i])
	{
		while (*line && *line[i] && (*line[i] != ' ' || *line[i] != '	'))
			i++;
		skip_space(line);
	}
	if (i > 0)
		comm->arguments = ft_substr(*line, 0, i);
	else
		comm->arguments = NULL;
}

void	fill_command(t_command *comm, char *line)
{
	get_command(comm, &line);
	get_options(comm, &line);
	get_args(comm, &line);
}
