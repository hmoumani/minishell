/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:25:18 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/21 21:53:40 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	slen;
	size_t	i;

	slen = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && i < slen)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (slen);
}
