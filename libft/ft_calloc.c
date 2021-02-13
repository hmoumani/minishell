/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 21:49:48 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/22 18:46:10 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc(nitems * size);
	if (!p)
		return (NULL);
	while (i < nitems * size)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
