/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:18:55 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/01 12:45:04 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern va_list	g_args;
extern int	g_minus;

int		ft_countdigits(long unsigned int n)
{
	int count;

	count = 1;
	while (n / 10)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int		ft_flag_number(char **f)
{
	int num;

	if (**f == '*')
		num = va_arg(g_args, int);
	else
	{
		num = ft_atoi(*f);
		if (ft_isdigit(**f))
			(*f) += ft_countdigits(num) - 1;
		else
			(*f)--;
	}
	return (num);
}

int		ft_flags(char **f)
{
	int		size;
	int		num;

	size = -1;
	if (**f == '*' || (**f > 48 && **f < 58))
		size = ft_flag_field_width(f, ft_flag_number(f));
	else if (**f == '-')
	{
		g_minus = 1;
		(*f)++;
		size = ft_args(f);
	}
	else if (**f == '.')
	{
		(*f)++;
		size = ft_flag_precision(f, ft_flag_number(f));
	}
	else if (**f == '0')
	{
		(*f)++;
		size = ft_flag_zero(f, ft_flag_number(f));
	}
	return (size);
}
