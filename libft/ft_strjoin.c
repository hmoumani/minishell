/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:08:50 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/16 23:48:24 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*cat;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	cat = malloc(len1 + len2 + 1);
	if (!cat)
		return (NULL);
	while (i < len1 + len2)
	{
		if (i < len1)
			cat[i] = s1[i];
		else
			cat[i] = s2[i - len1];
		i++;
	}
	cat[i] = '\0';
	return (cat);
}
