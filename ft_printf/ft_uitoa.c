/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:57:30 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/21 12:13:54 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*ft_special_cases(unsigned int n)
{
	char	*str;

	str = malloc(2);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char			*ft_uitoa(unsigned int n)
{
	int		count;
	char	*num;

	if (n == 0)
		return (ft_special_cases(n));
	count = ft_countdigits(n);
	if (!(num = malloc(count + 1)))
		return (NULL);
	num[count] = '\0';
	while (n)
	{
		num[--count] = n % 10 + 48;
		n /= 10;
	}
	return (num);
}
