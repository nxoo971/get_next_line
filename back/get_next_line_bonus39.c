/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus39.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:10:44 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/21 16:16:02 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	**arraydup(char **src)
{
	char	**dst;
	int		i;

	if (!src)
		return (src);
	i = 0;
	while (src[i])
		i++;
	i++;
	dst = malloc(sizeof(char *) * (i + 1));
	if (!dst)
		return (dst);
	dst[i] = 0;
	dst[--i] = malloc(1);
	dst[i][0] = '\0';
	while (--i >= 0)
		dst[i] = strdup(src[i]);
	return (dst);
}

int		readuntil(int fd, char **bufferline, char **endl)
{
	char	buff[BUFFER_SIZE + 1];
	int		byteread;

	byteread = 1;
	*endl = NULL;
	while (byteread)
	{
		byteread = read(fd, buff, BUFFER_SIZE);
		if (byteread < 0)
			return (byteread);
		if (byteread == 0)
			break ;
		ft_strjoin(bufferline, buff, byteread);
		*endl = strchr(bufferline, '\n');
		if (*endl)
			break ;
	}
	return (byteread);
}

char	**get_line_by_fd(int fd, char **tline)
{
	char	**res;
	int		size;
	int		i;

	i = 0;
	if (!tline)
	{
		size = fd;
		if (fd == 0)
			size = 2;
		tline = malloc(sizeof(char *) * size);
		if (tline)
		{
			while (i < size - 1)
			{
				tline[i] = malloc(1);
				if (!tline[i])
					return (freetab(tline));
				tline[i][0] = '\0';
				i++;
			}
			tline[i] = 0;
		}
		return (tline);
	}
	if (tline[fd == 0 ? fd : fd - 2])
		return (tline);
	res = arraydup(tline);
	freetab(tline);
	return (res);
}

char	**freetab2(char **buffer, int current)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i][0] != 0)
			count++;
		i++;
	}
	if (count == 0)
	{
		i = -1;
		while (buffer[++i])
			free(buffer[i]);
		free(buffer);
		buffer = NULL;
	}
	else
	{
		free(buffer[current]);
		buffer[current] = malloc(1);
		buffer[current][0] = 0;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	**buffer;
	char		*temp;
	char		*endl;
	int			byteread;
	int			pos;

	if (fd < 3 && fd != 0)
		return (freetab(buffer));

	buffer = get_line_by_fd(fd, buffer);
	pos = (fd == 0 ? fd : fd - 2);
	if (!buffer || !buffer[pos])
		return (freetab(buffer));

	temp = NULL;
	byteread = readuntil(fd, buffer + pos, &endl);
	if (!endl)
	{
		if (buffer[pos][0])
		{
			char *tmp = strdup(buffer[pos]);

			freetab2(buffer, pos);
			return (tmp);
		}
		freetab2(buffer, pos);
		return (NULL);
	}
	temp = strndup(buffer[pos], endl - buffer[pos] + 1);
	if (temp)
	{
		char *tmp = strdup(endl + 1);
		free(buffer[pos]);
		buffer[pos] = tmp;
	}
	return (temp);
}
