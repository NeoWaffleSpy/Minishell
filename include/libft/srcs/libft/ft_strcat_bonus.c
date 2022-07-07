/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:24:36 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:08:31 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	char		*d;
	char		*s;

	d = dst;
	s = (char *)src;
	while (*d != '\0')
		d++;
	while (*s != '\0')
	{
		*d++ = *s;
		s++;
	}
	*d = '\0';
	return (dst);
}
