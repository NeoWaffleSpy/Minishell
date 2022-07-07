/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 21:06:37 by ncaba             #+#    #+#             */
/*   Updated: 2022/04/27 10:59:50 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_itoa_size(int n)
{
	int				size;
	int				neg;

	size = 0;
	neg = 0;
	if (n < 0 && n > MININT)
	{
		neg = 1;
		size++;
		n = -n;
	}
	else if (n == 0)
		return (1);
	else if (n == MININT)
		return (11);
	while (n >= 1)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static double	ternary(int boo, double a, double b)
{
	if (boo)
		return (a);
	else
		return (b);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	int				size;
	unsigned int	tmp;

	if (n == MININT)
		return (ft_strdup("-2147483648"));
	size = ft_itoa_size(n);
	i = 1;
	str = (char *)malloc(sizeof(char) * ft_itoa_size(n) + 1);
	if (!str)
		return (NULL);
	tmp = (int)ternary(n < 0, (double)-n, (double)n);
	*str = (char)ternary(n < 0, (double) '-', (double) ' ');
	if (tmp == 0)
		str[tmp] = '0';
	while (tmp >= 1)
	{
		str[size - i] = (tmp % 10) + '0';
		tmp /= 10;
		i++;
	}
	str[size] = '\0';
	return (str);
}
