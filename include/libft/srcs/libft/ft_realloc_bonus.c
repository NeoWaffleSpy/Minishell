/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 23:04:05 by ncaba             #+#    #+#             */
/*   Updated: 2020/12/15 23:09:30 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_realloc(void *str, int new_size, int type)
{
	void	*new_str;

	new_str = malloc(new_size * type);
	ft_memcpy(new_str, str, new_size);
	free(str);
	return (new_str);
}
