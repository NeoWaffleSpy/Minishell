/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:26:22 by ncaba             #+#    #+#             */
/*   Updated: 2022/08/02 19:53:09 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_lstfadd_front(t_file **alst, t_file *new)
{
	if (!*alst)
	{
		*alst = new;
		return (1);
	}
	if (!new)
		return (1);
	new->next = *alst;
	*alst = new;
	return (1);
}

int	ft_lstfadd_back(t_file **alst, t_file *new)
{
	t_file	*last;

	if (!*alst)
	{
		*alst = new;
		return (1);
	}
	last = *alst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return (1);
}

void	ft_lstfclear(t_file **lst, void (*del)(void*))
{
	t_file	*tmp;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->filename);
		tmp = *lst;
		*lst = tmp->next;
		free_garbage(tmp);
	}
	*lst = NULL;
}

t_file	*ft_lstfnew(void *content, int append)
{
	t_file		*item;

	item = malloc_garbage(sizeof(t_file));
	if (!item)
		return (NULL);
	item->filename = content;
	item->is_append = append;
	item->next = NULL;
	return (item);
}

t_file	*ft_lstfget(t_file *lst, int i)
{
	while (lst && i > 0)
	{
		lst = lst->next;
		i--;
	}
	if (lst)
		return (lst);
	return (NULL);
}

int	ft_lstfsize(t_file *list)
{
	int	size;

	if (!list)
		return (0);
	size = 0;
	while (list)
	{
		size++;
		list = list->next;
	}
	return (size);
}

