/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_percent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:35:28 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 14:49:57 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

char	*ft_convert_percent(t_flags flags)
{
	char	*result;

	result = (char *)calloc(2, sizeof(char));
	result[0] = '%';
	ft_add_space(&result, flags, PERCENT);
	ft_add_padd(&result, flags, PERCENT);
	return (result);
}
