/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoullel <atoullel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:03:06 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/09 19:54:36 by atoullel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	file_check_next(t_command *comm, char ***split, char *msg)
{
	free_garbage(**split);
	(*split)++;
	if (*split && **split && ***split != '<' && ***split != '>'
		&& ***split != '|' && ***split != '&')
		return (1);
	comm->error = call_error("Syntax error:", msg, 2);
	return (0);
}

static int	file_redir(t_var *var, t_command *comm, char ***split)
{
	if (!comm->error && ft_strcmp(**split, "<") == 0)
		if (file_check_next(comm, split, "no file provided"))
			return (ft_lstfadd_back(&comm->infile, ft_lstfnew(**split, 0)));
	if (!comm->error && ft_strcmp(**split, "<<") == 0)
		if (file_check_next(comm, split, "no delim provided"))
			return (ft_lstfadd_back(&comm->infile, create_heredoc(var,
						ft_lstfnew(**split, 1))));
	if (!comm->error && ft_strcmp(**split, ">") == 0)
		if (file_check_next(comm, split, "no file provided"))
			return (ft_lstfadd_back(&comm->outfile, ft_lstfnew(**split, 0)));
	if (!comm->error && ft_strcmp(**split, ">>") == 0)
		if (file_check_next(comm, split, "no file provided"))
			return (ft_lstfadd_back(&comm->outfile, ft_lstfnew(**split, 1)));
	return (0);
}

static int	set_comm_2(char **split, t_command *comm)
{
	char	*tmp;

	tmp = *split;
	if (comm->command == NULL)
	{
		comm->command = clean_str(*split);
		return (1);
	}
	while (*tmp == '\"')
		tmp++;
	if (*tmp == '-')
	{
		ft_lstfadd_back(&comm->arguments, ft_lstfnew(clean_str(*split), 1));
		return (1);
	}
	return (0);
}

static t_command	*set_command(t_var *var, char **split)
{
	t_command	*comm;

	comm = init_comm();
	if (!*split || !ft_strcmp(*split, "|"))
		comm->error = call_error("Syntax error:", "Pipe de merde", 2);
	while (!comm->error && split && *split)
	{
		if (file_redir(var, comm, &split))
			;
		else if (comm->error)
			return (comm);
		else if (set_comm_2(split, comm))
			;
		else if (!ft_strcmp(*split, "|"))
		{
			comm->next = set_command(var, split + 1);
			if (comm->next->error != 0 && comm->error == 0)
				comm->error = comm->next->error;
			break ;
		}
		else
			ft_lstfadd_back(&comm->arguments, ft_lstfnew(clean_str(*split), 0));
		split++;
	}
	return (comm);
}

t_command	*fill_command(t_var *var, char *line)
{
	char		**split;
	t_command	*comm;

	comm = NULL;
	split = split_command(line);
	if (!split)
		call_error("Malloc a foired", "fill_command()", 2);
	else
		comm = set_command(var, split);
	free_garbage(split);
	return (comm);
}
