/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:47:08 by ojoubout          #+#    #+#             */
/*   Updated: 2019/10/20 16:02:25 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str, char c)
{
	int i;
	int sw;
	int wc;

	wc = 0;
	i = 0;
	sw = 1;
	while (str[i])
	{
		if (str[i] == c)
			sw = 1;
		else
		{
			if (sw)
			{
				wc++;
				sw = 0;
			}
		}
		i++;
	}
	return (wc);
}

static int	ft_word_length(const char *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**ft_free(char **ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	size_t	i;
	int		j;
	char	**split;
	int		wc;

	if (!s || ((wc = ft_countwords(s, c)) < 0))
		return (NULL);
	if (!(split = malloc((wc + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			if (!(split[j] = malloc(ft_word_length(&s[i], c) + 1)))
				return (ft_free(split, wc + 1));
			ft_strlcpy(split[j++], &s[i], ft_word_length(&s[i], c) + 1);
			i += ft_word_length(&s[i], c) + 1;
		}
		else
			i++;
	}
	split[j] = NULL;
	return (split);
}
