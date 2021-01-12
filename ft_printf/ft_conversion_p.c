/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:53:33 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/31 15:27:24 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int g_zero;

ssize_t	ft_conversion_p(void *p)
{
	char *str;
	char *buff;

	str = ft_convert((long unsigned int)p, 16, 'x');
	str = ft_strprs(str);
	g_zero = g_zero - 2;
	str = ft_strzero(str);
	buff = ft_strjoin("0x", str);
	free(str);
	return (ft_putstr(buff));
}
