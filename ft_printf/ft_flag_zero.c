/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:14:37 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/01 12:45:21 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			g_zero = 0;
extern int	g_arg;
extern int	g_field_width;
extern int	g_printzero;
extern int	g_minus;

ssize_t	ft_flag_zero(char **f, int n)
{
	g_zero = n > 0 ? n : 0;
	if (g_minus)
	{
		g_field_width = g_zero;
		g_zero = 0;
	}
	(*f)++;
	return (ft_args(f));
}

char	*ft_strzero(char *str)
{
	char	*buff;
	int		len;
	char	*s;

	len = ft_strlen(str) + g_printzero;
	buff = ft_strdup(str);
	s = str;
	if (g_zero > len)
	{
		if (str[0] == '-')
			g_zero++;
		free(buff);
		buff = malloc(g_zero + 1);
		ft_memset(buff, '0', g_zero);
		if (str[0] == '-')
		{
			buff[0] = '-';
			str++;
		}
		ft_strlcpy(buff + g_zero - len, str, len + 1);
	}
	free(s);
	return (buff);
}
