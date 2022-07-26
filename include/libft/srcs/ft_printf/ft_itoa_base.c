/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 14:52:33 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 15:06:54 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static char	*zero_case(char *base)
{
	char	*str;

	str = malloc_garbage(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = base[0];
	str[1] = '\0';
	return (str);
}

static int	base_size(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

static int	size_forecast(long long n, char *base)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	while (n > 0)
	{
		i++;
		n /= base_size(base);
	}
	return (i + sign);
}

static void	str_rev(char *str)
{
	int		i;
	int		size;
	char	temp;

	i = 0;
	size = 0;
	while (str[size])
		size++;
	size--;
	while (i < size - i)
	{
		temp = str[i];
		str[i] = str[size - i];
		str[size - i] = temp;
		i++;
	}
}

char	*ft_itoa_base(long long n, char *base)
{
	int		i;
	char	*str;
	int		neg;

	get_neg(&n, &neg);
	if (n == 0)
		return (zero_case(base));
	str = malloc_garbage(sizeof(char) * (size_forecast(n, base) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (n > 0)
	{
		str[i] = base[n % base_size(base)];
		i++;
		n /= base_size(base);
	}
	if (neg)
		str[i] = '-';
	str[i + neg] = '\0';
	str_rev(str);
	return (str);
}
