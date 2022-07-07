/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 18:52:04 by ncaba             #+#    #+#             */
/*   Updated: 2020/12/29 16:19:57 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_free_all(void **s)
{
	int	count;

	count = 0;
	while (s[count])
	{
		free(s[count]);
		count++;
	}
	free(s);
}
