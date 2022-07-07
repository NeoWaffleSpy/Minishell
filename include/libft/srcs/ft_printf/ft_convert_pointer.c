/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:36:00 by ncaba             #+#    #+#             */
/*   Updated: 2020/12/17 21:26:47 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

char	*ft_convert_pointer(t_flags flags, va_list params)
{
	char			*result;
	unsigned long	value;

	value = (unsigned long)va_arg(params, void *);
	result = ft_itoa_base(value, "0123456789abcdef");
	ft_add_precis(&result, flags);
	ft_alternative(&result, flags, POINTER);
	ft_add_space(&result, flags, POINTER);
	ft_add_padd(&result, flags, POINTER);
	return (result);
}
