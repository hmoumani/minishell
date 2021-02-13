/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 20:07:47 by ojoubout          #+#    #+#             */
/*   Updated: 2019/11/14 16:26:43 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_copy_line(char **line, char *buff, int ret, int r)
{
	char	*temp;
	char	*chr;
	char	*rest;

	buff[ret] = '\0';
	chr = NULL;
	temp = NULL;
	rest = NULL;
	if ((chr = ft_strchr(buff, '\n')))
	{
		*chr = '\0';
		rest = ft_strdup(chr + 1);
	}
	temp = *line;
	*line = ft_strjoin(*line, buff);
	if (temp != NULL)
		free(temp);
	if (r)
		free(buff);
	return (rest);
}

int		freepointer(char *buff, int ret)
{
	free(buff);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*rest[256] = {NULL};
	char		*buff;
	int			rr;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 0 ||
	!(buff = malloc(BUFFER_SIZE + 1)))
		return (-1);
	*line = ft_strdup("");
	if (rest[fd] != NULL)
		if ((rest[fd] = ft_copy_line(line, rest[fd], ft_strlen(rest[fd]), 1)))
			return (freepointer(buff, 1));
	while ((rr = read(fd, buff, BUFFER_SIZE)) > 0)
		if ((rest[fd] = ft_copy_line(line, buff, rr, 0)))
			break ;
	if (rr <= 0)
		return (freepointer(buff, rr));
	return (freepointer(buff, 1));
}
