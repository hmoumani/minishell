/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:57:30 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/14 17:02:32 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigits(int n)
{
	int count;

	count = 0;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char		*ft_special_cases(int n)
{
	char	*str;

	if (n == 0)
	{
		str = ft_calloc(2, 1);
		str[0] = '0';
	}
	else
	{
		str = malloc(12);
		ft_strlcpy(str, "-2147483648", 12);
	}
	return (str);
}

char		*ft_itoa(int n)
{
	int		neg;
	int		count;
	char	*num;

	if (n == 0 || n == -2147483648)
		return (ft_special_cases(n));
	count = ft_countdigits(n);
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		n = -n;
		count++;
	}
	if (!(num = malloc(count + 1)))
		return (NULL);
	num[count] = '\0';
	while (n)
	{
		num[--count] = n % 10 + 48;
		n /= 10;
	}
	if (neg)
		num[0] = '-';
	return (num);
}
