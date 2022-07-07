/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 22:53:00 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 14:50:58 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	move_sign(char *str)
{
	char	*tmp;

	tmp = str;
	while (*str != '-')
		str++;
	*str = '0';
	str = tmp;
	while (*str != '0')
		str++;
	*str = '-';
}

char	*ft_convert_int(t_flags flags, va_list params)
{
	int		value;
	char	*result;

	value = va_arg(params, int);
	result = ft_itoa(value);
	if (flags.nb_dec == 0 && ft_atoi(result) == 0)
		result[0] = '\0';
	ft_add_precis(&result, flags);
	if (ft_atoi(result) == 0 && flags.nb_dec == 0)
	{
		free(result);
		result = ft_calloc(2, sizeof(char));
	}
	ft_add_space(&result, flags, INT);
	ft_add_padd(&result, flags, INT);
	if (flags.is_padded_zero && value < 0)
		move_sign(result);
	return (result);
}
