/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 21:34:35 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/05 17:13:42 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**free_all(char **tab, int countdown)
{
	while (countdown >= 0)
	{
		free_garbage(tab[countdown]);
		countdown--;
	}
	free_garbage(tab);
	return (NULL);
}

static int	get_next_index(char *str)
{
	t_var	var;
	int		index;

	reset_var(&var);
	index = 0;
	if ((str[index] == '>' && str[index + 1] == '>')
		|| (str[index] == '<' && str[index + 1] == '<'))
		return (2);
	if (str[index] == '|' || str[index] == '>' || str[index] == '<')
		return (1);
	while (str[index] && ((str[index] != ' ' && str[index] != 9)
			|| var.quotes % 2 || var.dquotes % 2))
	{
		if ((str[index] == '|' || str[index] == '>' || str[index] == '<')
			&& !(var.quotes % 2) && !(var.dquotes % 2))
			return (index);
		if (!(var.quotes % 2) && str[index] == '\"')
			var.dquotes++;
		if (!(var.dquotes % 2) && str[index] == '\'')
			var.quotes++;
		index++;
	}
	return (index);
}

static int	get_nb_split(char *str)
{
	int		nb_split;

	nb_split = 0;
	while (*str && (*str == ' ' || *str == 9))
		str++;
	str += get_next_index(str);
	while (*str)
	{
		nb_split++;
		while (*str && (*str == ' ' || *str == 9))
			str++;
		str += get_next_index(str);
	}
	return (nb_split + 1);
}

static int	init(int *index_tab, char *str, char ***tab)
{
	*index_tab = 0;
	if (!str)
		return (0);
	*tab = malloc_garbage(sizeof(char *) * (get_nb_split(str) + 1));
	if (!*tab)
		return (0);
	return (1);
}

char	**split_command(char *str)
{
	char	**tab;
	int		index;
	int		index_tab;

	if (init(&index_tab, str, &tab) == 0)
		return (NULL);
	while (*str)
	{
		while (*str && (*str == ' ' || *str == 9))
			str++;
		if (*str)
		{
			index = get_next_index(str);
			tab[index_tab] = ft_substr(str, 0, index);
			if (!tab[index_tab])
				return (free_all(tab, index_tab));
			index_tab++;
			str += index;
		}
	}
	tab[index_tab] = 0;
	return (tab);
}
