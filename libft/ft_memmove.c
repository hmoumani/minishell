/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:43:48 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/22 11:53:20 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memrcpy(void *dst, const void *src, size_t n)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = n - 1;
	while (i >= 0)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i--;
	}
	return (dst);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (NULL);
	if ((char *)dst > (char *)src)
		ft_memrcpy(dst, src, len);
	else if ((char *)dst < (char *)src)
		ft_memcpy(dst, src, len);
	return (dst);
}
