/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 22:04:44 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/01 17:13:25 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	char	*c;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	c = malloc(len + 1);
	if (!c)
		return (NULL);
	ft_strlcpy(c, src, len + 1);
	return (c);
}
