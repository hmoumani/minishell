/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:50:13 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/31 10:14:18 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert(long unsigned int num, int base, char x)
{
	static char	*rep1 = "0123456789ABCDEF";
	static char	*rep2 = "0123456789abcdef";
	static char	buffer[50];
	char		*ptr;

	ptr = &buffer[49];
	*ptr = '\0';
	if (x == 'X')
		*--ptr = rep1[num % base];
	else
		*--ptr = rep2[num % base];
	num /= base;
	while (num != 0)
	{
		if (x == 'X')
			*--ptr = rep1[num % base];
		else
			*--ptr = rep2[num % base];
		num /= base;
	}
	return (ft_strdup(ptr));
}
