/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:45:33 by ncaba             #+#    #+#             */
/*   Updated: 2022/07/26 23:01:32 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*malloc_garbage(size_t size)
{
	void	*item;

	item = malloc(size);
	if (!item)
		return (NULL);
	if (g_garbage == NULL)
		g_garbage = ft_lstnew(item);
	else
		ft_lstadd_front(&g_garbage, ft_lstnew(item));
	return (item);
}

void	free_garbage(void *trash)
{
	t_list	*tmp;
	t_list	*back;

	tmp = g_garbage;
	back = NULL;
	while (tmp && tmp->content != trash)
	{
		back = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		ft_putstr("Cannot find the specified item in the garbage can\n");
	else
	{
		if (back == NULL)
			g_garbage = tmp->next;
		else
			back->next = tmp->next;
		free(tmp);
	}
	free(trash);
}

void	dump_trash(void)
{
	ft_lstclear(&g_garbage, free);
}

void	add_garbage(void *trash)
{
	ft_lstadd_front(&g_garbage, ft_lstnew(trash));
}
