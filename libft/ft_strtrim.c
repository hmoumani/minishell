/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:18:44 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/22 12:22:07 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_charcont(const char *str, char c)
{
	int i;
	int cont;

	cont = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			cont++;
		i++;
	}
	return (cont);
}

static void	ft_strtrimlen(char const *s1, char const *set, int *nlen)
{
	int i;

	i = 0;
	while (s1[i] && ft_charcont(set, s1[i]))
		i++;
	nlen[0] = i;
	i = ft_strlen(s1) - 1;
	while (i && ft_charcont(set, s1[i]))
		i--;
	nlen[1] = i;
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		len[2];
	char	*trim;

	if (!s1 || !set)
		return (NULL);
	ft_strtrimlen(s1, set, len);
	if (len[0] > len[1])
	{
		trim = (char*)malloc(1);
		if (trim == NULL)
			return (NULL);
		trim[0] = '\0';
		return (trim);
	}
	trim = malloc(len[1] - len[0] + 2);
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, s1 + len[0], len[1] - len[0] + 2);
	return (trim);
}
