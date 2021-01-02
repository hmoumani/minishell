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

int		ft_is_backslashed(const char *str, int i)
{
	int is_backslashed;

	i--;
	is_backslashed = 0;
	while (i >= 0 && str[i] == '\\')
	{
		is_backslashed = !is_backslashed;
		i--;
	}
	return (is_backslashed);
}

int		ft_is_quoted(const char *str, int i)
{
	int quote[2];
	int j;

	ft_bzero(quote, 2);
	j = 0;
	while (j <= i)
	{
		if (!quote[0] && (str[j] == '"' || str[j] == '\'') && !ft_is_backslashed(str, j))
			quote[0] = str[j];
		else if ((quote[0] == '\'' && str[j] == '\'') ||
		(quote[0] == '"' && str[j] == '\"' && !ft_is_backslashed(str, j)))
			quote[0] = 0;
		j++;
	}
	return (quote[0] == '\'');
}

int	ft_on_char(const char *str, int i, char *c)
{
	int		j;
	char	*quote[2];

	j = 0;
	ft_bzero(quote, 2);
	while (c[j])
	{
		if (str[i] == c[j])
			if (i == 0 || (!ft_is_backslashed(str, i) && !ft_is_quoted(str, i)))
				return 1;
		j++;
	}
	return 0;
}

int	ft_strequ(char *s1, char *s2)
{
	int len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	return (ft_strncmp(s1, s2, len + 1) == 0);	
}

char	*ft_strappend(char *str, char c)
{
	char strchar[2];

	strchar[0] = c;
	strchar[1] = 0;
	return (ft_strjoin(str, strchar));	
}

char	*ft_quotes_convert(char *str)
{
	int 	i;
	char 	*res;
	char	*tmp;
    char    quote[2];

	i = 0;
	ft_bzero(quote, 2);
	res = ft_strdup("");
	while (str[i])
	{
		if (quote[0] != '\'' && ft_on_char(str, i, "\\"))
		{
			i++;
			continue;
		}
		if ((!quote[0] && ft_on_char(str, i, "'\"")) || ft_on_char(str, i, quote))
		{
			quote[0] = quote[0] ? 0 : str[i];
        } else {
			tmp = res;
			res = ft_strappend(res, str[i]);
			free(tmp);
		}
        i++;
	}
	return (res);
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
