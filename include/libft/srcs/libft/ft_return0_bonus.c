/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_return0_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 12:56:18 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:31:06 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_return0(void)
{
	void	*s;

	s = malloc(sizeof(char));
	if (!s)
		return (NULL);
	*(char *)s = '\0';
	return (s);
}
