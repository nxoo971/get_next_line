/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:10:44 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/20 20:39:40 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*newline_exist(char **line, int lastline)
{
	const char	*endl;
	char		*res;
	char		*tmp;

	if (!*line)
		return (*line);
	tmp = NULL;
	endl = strchr(*line, '\n');
	if (endl && !lastline)
	{
		tmp = strdup(endl + 1);
		res = strndup(*line, (endl - *line) + 1);
		free(*line);
		*line = tmp;
		return (res);
	}
	if (lastline && **line && !endl)
		tmp = strdup(*line);
	if (tmp || (*line && !**line))
	{
		free(*line);
		*line = malloc(1);
		**line = 0;
	}
	return (tmp);
}

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

char	**is_lastline(char **tline, int fd)
{
	char	**res;
	char	buff[BUFFER_SIZE + 1];
	int		byteread;
	int		pos;

	pos = fd - 2;
	if (fd == 0)
		pos = 0;
	if (tline[pos])
	{
		if (tline[pos][0])
			return (tline);
		readfile(fd, buff, &byteread);
		if (byteread <= 0)
			return (freetab(tline));
		ft_strjoin(tline + pos, buff, byteread);
		return (tline);
	}
	res = arraydup(tline);
	freetab(tline);
	return (res);
}

char	**check_line_by_fd(char	**tline, int fd)
{
	int		size;

	if (!tline)
	{
		size = fd;
		if (fd == 0)
			size = 2;
		tline = malloc(sizeof(char *) * size);
		if (tline)
		{
			tline[size] = 0;
			while (--size >= 0)
			{
				tline[size] = malloc(1);
				tline[size][0] = '\0';
			}
		}
		return (tline);
	}
	return (is_lastline(tline, fd));
}

char	*get_next_line(int fd)
{
	static char	**tline;
	char		**line;
	char		*res;
	char		buff[BUFFER_SIZE + 1];
	int			byteread;

	if (fd < 3 && fd != 0)
		return (NULL);
	tline = check_line_by_fd(tline, fd);
	if (!tline)
		return (NULL);
	line = tline + fd - 2;
	if (fd == 0)
		line = tline + fd;
	byteread = 1;
	while (byteread)
	{
		readfile(fd, buff, &byteread);
		if (byteread < 0)
			return (NULL);
		ft_strjoin(line, buff, byteread);
		res = newline_exist(line, 0);
		if (res)
			return (res);
	}
	return (newline_exist(line, 1));
}
/*
int		main(int ac, char **av)
{
	(void)ac;
	char	*res;
	int		fd = open(av[1], O_RDONLY);
	int		fd2 = open(av[2], O_RDONLY);

	// while ((res = get_next_line(fd)))
	// 	printf("%s", res);
	// printf("%s", res);
	res = get_next_line(fd);
	printf("1: %s", res);
	res = get_next_line(fd2);
	printf("2: %s", res);
	res = get_next_line(fd);
	printf("3: %s", res);
	res = get_next_line(fd2);
	printf("4: %s", res);
	res = get_next_line(fd);
	printf("5: %s", res);
	res = get_next_line(fd2);
	printf("6: %s", res);
	res = get_next_line(fd);
	printf("7: %s", res);
	res = get_next_line(fd2);
	printf("8: %s", res);

	res = get_next_line(fd);
	printf("9: %s", res);
	res = get_next_line(fd2);
	printf("10: %s", res);
	res = get_next_line(fd);
	printf("11: %s", res);
	res = get_next_line(fd2);
	printf("12: %s", res);

	close(fd);
	close(fd2);
	return (0);
}
*/