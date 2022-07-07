/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:01:42 by ncaba             #+#    #+#             */
/*   Updated: 2020/12/03 19:04:02 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_pow(int chiffre, int expo)
{
	int	res;
	int	loop;

	res = 1;
	loop = 0;
	while (loop < expo)
	{
		res *= chiffre;
	}
	return (chiffre);
}
