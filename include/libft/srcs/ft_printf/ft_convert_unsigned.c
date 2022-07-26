/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_unsigned.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:36:29 by ncaba             #+#    #+#             */
/*   Updated: 2020/12/19 16:22:04 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

char	*ft_convert_unsigned(t_flags flags, va_list params)
{
	char				*result;
	long unsigned int	value;

	value = va_arg(params, unsigned int);
	result = ft_itoa_base(value, "0123456789");
	ft_add_precis(&result, flags);
	if (ft_atoi(result) == 0 && flags.nb_dec == 0)
	{
		free_garbage(result);
		result = ft_calloc(2, sizeof(char));
	}
	ft_add_space(&result, flags, U_INT);
	ft_add_padd(&result, flags, U_INT);
	return (result);
}
