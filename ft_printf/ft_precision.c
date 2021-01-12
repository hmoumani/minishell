/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:02:02 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/01 16:36:54 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	g_precision = -1;
extern int g_arg;
extern int g_zero;
extern int g_field_width;

ssize_t	ft_flag_precision(char **f, int n)
{
	g_precision = n >= 0 ? n : -1;
	g_field_width += g_zero;
	g_zero = 0;
	(*f)++;
	return (ft_args(f));
}

char	*ft_strprs(char *str)
{
	char	*buff;
	size_t	slen;
	char	*s;

	slen = ft_strlen(str);
	buff = ft_strdup(str);
	s = str;
	if (g_precision == 0 && ft_strncmp(str, "0", 1) == 0)
		buff[g_precision] = '\0';
	else if (g_precision >= (int)slen)
	{
		if (str[0] == '-')
			g_precision++;
		free(buff);
		buff = malloc(g_precision + 1);
		ft_memset(buff, '0', g_precision);
		if (str[0] == '-' && (buff[0] = '-'))
		{
			str++;
			slen--;
		}
		ft_strlcpy(buff + g_precision - slen, str, slen + 1);
	}
	free(s);
	return (buff);
}
