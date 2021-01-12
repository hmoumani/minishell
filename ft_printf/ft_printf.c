/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:18:57 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/01 08:33:15 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

va_list		g_args;
extern int	g_precision;
extern int	g_minus;
extern int	g_printzero;
extern int	g_field_width;
extern int	g_zero;
int			g_cp = 0;

int			ft_args(char **f)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	if (**f == '%')
		size = ft_conversion_c('%');
	else if (**f == 'c')
		size = ft_conversion_c(va_arg(g_args, int));
	else if (**f == 's')
		size = ft_conversion_s(ft_strdup(va_arg(g_args, char *)));
	else if (**f == 'p')
		size = ft_conversion_p(va_arg(g_args, void *));
	else if (**f == 'd' || **f == 'i')
		size = ft_conversion_d_i(va_arg(g_args, int));
	else if (**f == 'u')
		size = ft_conversion_u(va_arg(g_args, unsigned int));
	else if (**f == 'x' || **f == 'X')
		size = ft_conversion_x(va_arg(g_args, unsigned int), **f);
	else if (**f != 0 && (i = ft_flags(f)) == -1)
		size = write(g_fd, *f, 1);
	if (i > 0)
		size += i;
	return (size < 0 ? 0 : size);
}

void		ft_reset(void)
{
	g_field_width = 0;
	g_precision = -1;
	g_zero = 0;
	g_minus = 0;
	g_printzero = 0;
}

int			ft_fprintf(int fd, const char *format, ...)
{
	char	*f;
	char	*str;
	int		size;

	size = 0;
	g_fd = fd;
	f = (char *)format;
	va_start(g_args, format);
	while (*f != '\0')
	{
		if (*f != '%')
			size += write(g_fd, f, 1);
		else
		{
			ft_reset();
			f++;
			size += ft_args(&f);
		}
		if (*f != '\0')
			f++;
	}
	va_end(g_args);
	return (size);
}
