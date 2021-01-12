/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:53:47 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/01 08:55:32 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_precision;
extern int	g_field_width;
extern int	g_zero;

ssize_t	ft_conversion_s(char *s)
{
	if (s == 0)
		s = ft_strdup("(null)");
	if (g_precision >= 0 && g_precision < ft_strlen(s))
	{
		free(s);
		s = ft_strdup(s);
		s[g_precision] = '\0';
	}
	g_precision = -1;
	s = ft_strzero(s);
	return (ft_putstr(s));
}
