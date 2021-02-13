/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:42:07 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/22 11:38:40 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	temp;

	i = 0;
	while (i < n)
	{
		temp = *((unsigned char *)src + i);
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
		if (temp == (unsigned char)c)
			return (dst + i);
	}
	return (NULL);
}
