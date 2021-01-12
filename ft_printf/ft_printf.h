/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:09:10 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/23 21:55:29 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include "../libft/libft.h"

int g_fd;

ssize_t		ft_putstr(char *s);
ssize_t		ft_putnbr(long n);
ssize_t		ft_conversion_c(char c);
ssize_t		ft_conversion_s(char *s);
ssize_t		ft_conversion_p(void *p);
ssize_t		ft_conversion_d_i(int n);
ssize_t		ft_conversion_u(unsigned int n);
ssize_t		ft_conversion_x(unsigned int n, char x);
int			ft_flags(char **f);
ssize_t		ft_flag_field_width(char **f, int n);
ssize_t		ft_flag_precision(char **f, int n);
ssize_t		ft_flag_zero(char **f, int n);
int			ft_countdigits(long unsigned int n);
char		*ft_convert(long unsigned int num, int base, char x);
char		*ft_uitoa(unsigned int n);

char		*ft_strprs(char *str);
char		*ft_strzero(char *str);
int			ft_args(char **f);
int			ft_fprintf(int fd, const char *format, ...);

#endif
