/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:23:43 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:46:32 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstdelone(t_list *alst, void (*del)(void *))
{
	if (!alst)
		return ;
	del(alst->content);
	free_garbage(alst);
}
