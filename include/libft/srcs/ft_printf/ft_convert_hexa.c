/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:34:07 by ncaba             #+#    #+#             */
/*   Updated: 2020/12/29 15:39:46 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

char	*ft_convert_hexa(t_flags flags, va_list params, t_boolean is_up)
{
	char				*result;
	long unsigned int	value;
	int					type;

	type = HEX_LOW;
	if (is_up)
		type = HEX_UP;
	value = va_arg(params, unsigned int);
	if (is_up)
		result = ft_itoa_base(value, "0123456789ABCDEF");
	else
		result = ft_itoa_base(value, "0123456789abcdef");
	ft_add_precis(&result, flags);
	if (result[0] == '0' && result[1] == '\0' && flags.nb_dec == 0)
	{
		free_garbage(result);
		result = ft_calloc(2, sizeof(char));
	}
	ft_add_space(&result, flags, type);
	ft_add_padd(&result, flags, type);
	ft_alternative(&result, flags, type);
	return (result);
}
