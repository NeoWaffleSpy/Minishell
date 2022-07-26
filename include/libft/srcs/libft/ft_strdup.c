/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 15:10:29 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:07:26 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_string;
	int		index;

	if (!s)
		return (NULL);
	if (*s == '\0')
		return ((char *)ft_calloc(sizeof(char), (ft_strlen(s) + 1)));
	new_string = malloc_garbage(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_string)
		return (NULL);
	index = 0;
	while (s[index])
	{
		new_string[index] = s[index];
		index++;
	}
	new_string[index] = '\0';
	return (new_string);
}
