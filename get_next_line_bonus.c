/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:10:44 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/14 20:10:48 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strndup(const char *s1, int len)
{
	char	*res;
	int		size;
	int		i;

	size = len;
	if (size == -1)
		size = ft_strlen(s1);
	res = malloc(size + 1);
	if (!res)
		return (res);
	i = -1;
	while (s1[++i] && i < size)
		res[i] = s1[i];
	res[i] = 0;
	return (res);
}

char	*newline_exist(char **line, int lastline)
{
	const char	*endl;
	char		*res;
	char		*tmp;

	if (!*line)
		return (*line);
	tmp = NULL;
	endl = ft_strchr(*line, '\n');
	if (endl && !lastline)
	{
		tmp = ft_strndup(endl + 1, -1);
		res = ft_strndup(*line, (endl - *line) + 1);
		free(*line);
		*line = tmp;
		return (res);
	}
	if (lastline && **line && !endl)
		tmp = ft_strndup(*line, -1);
	if (tmp || (*line && !**line))
	{
		free(*line);
		*line = NULL;
	}
	return (tmp);
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**copyarray(char **tab, int *size)
{
	char	**res;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	*size = i;
	if (!res)
		return (res);
	i = -1;
	while (tab[++i])
		res[i] = ft_strndup(tab[i], -1);
	return (res);
}

char	*check_fd(char **tline, int fd)
{
	char	**tmp;
	int		size;
	int		pos;

	if (!tline)
	{
		tline = malloc(sizeof(char *));
		*tline = ft_strndup("", -1);
		return (*tline);
	}
	pos = 0;
	if (fd != 0)
		pos = fd - (fd - 1);
	if (tline[pos])
		return (tline[pos]);
	tmp = copyarray(tline, &size);
	freetab(tline);
	tline = malloc((size + 1) * sizeof(char *));
	if (!tline)
		return (NULL);
	tline = tmp;
	tline[pos] = ft_strndup("", -1);
	return (tline[pos]);
}

char	*get_next_line(int fd)
{
	static char	**tline;
	char		*line;
	char		*res;
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 3 && fd != 0)
		return (NULL);
	line = check_fd(tline, fd);
	if (!line)
		return (line);
	ret = 1;
	while (ret)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buff[ret] = 0;
		ft_strjoin(&line, buff, ret);
		res = newline_exist(&line, 0);
		if (res)
			return (res);
	}
	return (newline_exist(&line, 1));
}

#include <stdio.h>
int		main(int ac, char **av)
{
	(void)ac;
	char	*res;
	int		fd = open(av[1], O_RDONLY);

	int		fd2 = open(av[2], O_RDONLY);

	res = get_next_line(fd);
	printf("1: %s", res);
	res = get_next_line(fd2);
	printf("2: %s", res);
	res = get_next_line(fd);
	printf("3: %s", res);
	res = get_next_line(fd2);
	printf("4: %s", res);
	res = get_next_line(fd);
	printf("4: %s", res);
	res = get_next_line(fd2);
	printf("4: %s", res);
	res = get_next_line(fd);
	printf("4: %s", res);
	res = get_next_line(fd2);
	printf("4: %s", res);

	close(fd);
	close(fd2);
	return (0);
}
