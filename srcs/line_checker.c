/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:03:06 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/05 17:00:44 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	file_check_next(t_command *comm, char ***split, char *msg)
{
	free_garbage(**split);
	(*split)++;
	if (*split && **split && (ft_isalnum(***split) || ***split == '_'))
		return (1);
	comm->error = call_error("Syntax error:", msg, 2);
	return (1);
}

static int	file_redir(t_command *comm, char ***split)
{
	if (ft_strcmp(**split, "<") == 0)
		if (file_check_next(comm, split, "no file provided"))
			return (ft_lstfadd_front(&comm->infile, ft_lstfnew(**split, 0)));
	if (ft_strcmp(**split, "<<") == 0)
		if (file_check_next(comm, split, "no delim provided"))
			return (ft_lstfadd_front(&comm->infile, ft_lstfnew(**split, 1)));
	if (ft_strcmp(**split, ">") == 0)
		if (file_check_next(comm, split, "no file provided"))
			return (ft_lstfadd_front(&comm->outfile, ft_lstfnew(**split, 0)));
	if (ft_strcmp(**split, ">>") == 0)
		if (file_check_next(comm, split, "no file provided"))
			return (ft_lstfadd_front(&comm->outfile, ft_lstfnew(**split, 1)));
	return (0);
}

static t_command	*set_command(char **split)
{
	t_command	*comm;

	comm = init_comm();
	while (split && *split)
	{
		if (file_redir(comm, &split))
			;
		else if (comm->command == NULL)
			comm->command = *split;
		else if (**split == '-')
			ft_lstadd_back(&comm->options, ft_lstnew(clean_str(*split)));
		else if (!ft_strcmp(*split, "|"))
		{
			comm->next = set_command(split + 1);
			if (comm->next->error != 0 && comm->error == 0)
				comm->error = comm->next->error;
			free_garbage(*split);
			break ;
		}
		else
			ft_lstadd_back(&comm->arguments, ft_lstnew(clean_str(*split)));
		split++;
	}
	return (comm);
}

t_command	*fill_command(char *line)
{
	char		**split;
	t_command	*comm;

	split = split_command(line);
	comm = set_command(split);
	free_garbage(split);
	return (comm);
}
