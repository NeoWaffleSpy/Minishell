/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:40:31 by ncaba             #+#    #+#             */
/*   Updated: 2020/11/30 16:04:23 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_tab;

	new_tab = malloc(size * nmemb);
	if (new_tab)
		ft_bzero(new_tab, size * nmemb);
	return (new_tab);
}
