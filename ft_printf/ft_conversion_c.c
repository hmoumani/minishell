/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:52:38 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/21 12:30:38 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			g_printzero = 0;
extern int	g_zero;

ssize_t	ft_conversion_c(char c)
{
	char *s;

	s = malloc(2);
	s[0] = c;
	s[1] = '\0';
	if (c == 0)
		g_printzero = 1;
	if (g_zero)
		s = ft_strzero(s);
	return (ft_putstr(s));
}
