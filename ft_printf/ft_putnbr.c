/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:15:30 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/31 11:36:28 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_putnbr(long n)
{
	char *s;

	if (n > 2147483647)
		s = ft_uitoa(n);
	else
		s = ft_itoa(n);
	s = ft_strprs(s);
	s = ft_strzero(s);
	return (ft_putstr(s));
}
