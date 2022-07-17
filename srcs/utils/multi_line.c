/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:36:25 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/17 20:04:21 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_quotes(char *line, t_var *var)
{
	while (*line)
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

	while (var->quotes % 2 || var->dquotes % 2)
	{
		if (var->quotes % 2)
			newline = readline("quote> ");
		else if (var->dquotes % 2)
			newline = readline("dquote> ");
		count_quotes(newline, var);
		tmp = ft_str_nl_join(line, newline);
		free(line);
		free(newline);
		line = tmp;
	}
	var->quotes = 0;
	var->dquotes = 0;
	return (tmp);
}
