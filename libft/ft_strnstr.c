/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:39:11 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/21 16:10:12 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	while (*(str + i) && (i + ft_strlen(to_find)) <= n)
	{
		if (*(str + i) == *to_find)
		{
			j = 0;
			while (*(to_find + j) && *(str + i + j) == *(to_find + j))
			{
				if (!*(to_find + j + 1))
				{
					return ((char *)str + i);
				}
				j++;
			}
		}
		i++;
	}
	if (*to_find == '\0')
		return ((char *)str);
	else
		return (0);
}
