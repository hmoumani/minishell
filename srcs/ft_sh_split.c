/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:56:59 by ojoubout          #+#    #+#             */
/*   Updated: 2020/12/13 13:57:00 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_on_char(const char *str, int i, char *c)
{
	int j;

	j = 0;
	while (c[j])
	{
		if (str[i] == c[j])
			if (i == 0 || str[i - 1] != '\\')
				return 1;
		j++;
	}
	return 0;
}

static int	ft_countwords(const char *str, char *c)
{
	int     i;
	int     sw;
	int     wc;
	char	quote[2];

	wc = 0;
	i = 0;
	sw = 1;
	ft_bzero(quote, 2);
	while (str[i])
	{
		if (!quote[0] || ft_on_char(str, i, quote))
		{
			/* check if i hit SPECIAL CHARACTER quote (shouldn't be backslash before it) */
			if (ft_on_char(str, i, "'\""))
					quote[0] = quote[0] ? 0 : str[i];
			if (ft_on_char(str, i, c))
				sw = 1;
			else
			{
				if (sw)
				{
					wc++;
					sw = 0;
				}
			}
		}
		i++;
	}
	return (wc);
}

int	ft_word_length(const char *s, char *c)
{
	int i;
	char    quote[2];

	i = 0;
	ft_bzero(quote, 2);
	while (s[i])
	{
		if (!quote[0] || ft_on_char(s, i, quote))
		{
			if (ft_on_char(s, i, "'\""))
					quote[0] = quote[0] ? 0 : s[i];
			if (ft_on_char(s, i, c))
				break;
		}
		i++;
	}
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

char		**ft_sh_split(char const *s, char *c)
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
		if (ft_on_char(s, i, c) == 0)
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
