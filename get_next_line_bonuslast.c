/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:10:44 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/20 21:51:33 by ooxn             ###   ########.fr       */
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

char	*readfile(int fd, char *buff, int *byteread)
{
	*byteread = read(fd, buff, BUFFER_SIZE);
	if (*byteread < 0)
		return (buff);
	buff[*byteread] = 0;
	return (buff);
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

char	*get_next_line(int fd)
{
	static char	**buffer;
	char		buff[BUFFER_SIZE + 1];
	char		*temp;
	const char	*endl;
	int			byteread;
	int			pos;

	if ((fd < 3 && fd != 0))
		return (freetab(buffer));

	temp = NULL;
	pos = (fd == 0 ? fd : fd - 2);
	buffer = get_line_by_fd(fd, buffer);
	byteread = 0;
	if (!buffer || !buffer[pos])
		return (freetab(buffer));
	while (readfile(fd, buff, &byteread))
	{
		if (byteread < 0)
			return (NULL);
		if (byteread == 0)
			break ;
		ft_strjoin(buffer + pos, buff, byteread);
		if (strchr(buff, '\n'))
			break ;
	}
	endl = strchr(buffer[pos], '\n');
	if (endl)
	{
		temp = strndup(buffer[pos], (endl - buffer[pos]) + 1);
		if (!temp)
			return (NULL);
		free(buffer[pos]);
		buffer[pos] = strdup(endl + 1);
		return (temp);
	}
	if (byteread == 0 && !temp)
	{
		if (buffer && buffer[pos][0])
		{
			temp = strdup(buffer[pos]);
			if (!temp)
				return (freetab(buffer));
			free(buffer[pos]);
			buffer[pos] = malloc(1);
			buffer[pos][0] = '\0';
			return (temp);
		}
		if (buffer && !buffer[pos][0])
		{
			readfile(fd, buff, &byteread);
			if (byteread <= 0)
				return (freetab(buffer));
			ft_strjoin(buffer + pos, buff, byteread);
			return (buffer[pos]);
		}
	}
	return (freetab(buffer));
}
