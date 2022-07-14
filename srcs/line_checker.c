/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:03:06 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/14 22:45:36 by ncaba            ###   ########.fr       */
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
	ft_printf("pass 1\n");
	skip_space(line);
	ft_printf("pass 2\n");
	while (*line && (*line)[i] && (*line)[i] != ' ' && (*line)[i] != '	')
		i++;
	ft_printf("pass 3\n");
	comm->command = ft_substr(*line, 0, i);
	ft_printf("pass 4\n");
	*line += i;
	skip_space(line);
	ft_printf("pass 5\n");
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
	ft_printf("%s\n", comm->options);
	*line += i;
}

static void	get_args(t_command *comm, char **line)
{
	int		i;
	char	*str;

	i = 0;
	while (*line && (*line)[i] && (*line)[i] != '-')
	{
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
	comm = malloc(sizeof(t_command));
	comm->command = NULL;
	comm->options = NULL;
	comm->arguments = NULL;
	comm->next = NULL;
	get_command(comm, &line);
	while (*line && *line != '|')
	{
		ft_printf("Pass 1\n");
		if (*line == '-')
			get_options(comm, &line);
		if (ft_isalnum(*line))
			get_args(comm, &line);
	}
	clean_str(&comm->command);
	clean_str(&comm->options);
	clean_str(&comm->arguments);
	if (*line == '|')
		comm->next = fill_command(line);
	return (comm);
}
