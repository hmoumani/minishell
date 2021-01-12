/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 13:15:46 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/31 14:11:18 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_field_width;
extern int	g_precision;
extern int	g_zero;
extern int	g_minus;
extern int	g_printzero;

ssize_t	ft_putstr(char *s)
{
	int		len;
	int		b;
	int		size;
	char	*buff;

	len = ft_strlen(s) + g_printzero;
	b = g_field_width - len;
	size = len + (b > 0 ? b : 0) + 1;
	buff = (char *)malloc(size);
	buff = ft_memset(buff, ' ', size);
	ft_memcpy(buff + (g_minus == 1 ? 0 : (size - 1 - len)), s, len);
	buff[size - 1] = '\0';
	len = write(g_fd, buff, size - 1);
	free(buff);
	free(s);
	g_field_width = 0;
	g_precision = -1;
	g_zero = 0;
	g_minus = 0;
	g_printzero = 0;
	return (len);
}
