/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_field_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:01:38 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/29 16:29:51 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	g_field_width = 0;
int	g_minus = 0;
extern int g_arg;

ssize_t	ft_flag_field_width(char **f, int n)
{
	g_field_width = n > 0 ? n : -n;
	g_minus = n < 0 ? 1 : g_minus;
	(*f)++;
	return (ft_args(f));
}
