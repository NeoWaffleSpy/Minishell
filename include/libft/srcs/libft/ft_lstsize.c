/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:28:35 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:42:03 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_lstsize(t_list *list)
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
