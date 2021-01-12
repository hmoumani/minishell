/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_x.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:52:38 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/31 11:35:05 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_conversion_x(unsigned int n, char x)
{
	char *str;

	str = ft_convert(n, 16, x);
	str = ft_strprs(str);
	str = ft_strzero(str);
	return (ft_putstr(str));
}
