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

#include "get_next_line_bonus.h"

static char	*ft_strndup(const char *s1, int len)
{
	char	*res;
	int		i;

	res = malloc(len + 1);
	if (!res)
		return (res);
	i = -1;
	while (s1[++i] && i < len)
		res[i] = s1[i];
	res[i] = 0;
	return (res);
}

static char	*ft_strdup(const char *s1)
{
	char	*res;
	int		size;
	int		i;

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

char	**copyarray(char **tab, int size)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * ((size) + 1));
	if (!res)
		return (res);
	i = 0;
	while (i < size)
	{
		if (tab[i])
			res[i] = ft_strdup(tab[i]);
		else
			res[i] = ft_strdup("");
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**check_fd(char **tline, int pos)
{
	char	**tmp;
	int		i;

	if (!tline)
	{
		tline = malloc(sizeof(char *) * ((pos+1) + 1));
		i = -1;
		while (++i < pos + 1)
			tline[i] = ft_strdup("");
		tline[i] = 0;
		return (tline);
	}
	if (tline[pos])
		return (tline);
	tmp = copyarray(tline, pos + 1);
	freetab(tline);
	return (tmp);
}

void	freetab2(char **tab, int pos)
{
	if (!tab)
		return ;
	int	i;

	i = 0;
	while (i < pos)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

char	*newline_exist(char **line, char **tline, int pos, int lastline)
{
	const char	*endl;
	char		*res;
	char		*tmp;

(void)tline;
	if (!*line)
		return (*line);
	tmp = NULL;
	endl = ft_strchr(*line, '\n');
	if (endl && !lastline)
	{
		tmp = ft_strdup(endl + 1);
		res = ft_strndup(*line, (endl - *line) + 1);
		free(*line);
		*line = tmp;
		return (res);
	}
	if (lastline && **line && !endl)
		tmp = ft_strdup(*line);
	if (tmp || (*line && !**line))
	{
		free(*line);
		*line = NULL;
		*line = ft_strdup("");
		//free(tline);
	}
	int count = 0;
	for (int i = 0; i < pos; i++)
		if (tline[i][0])
			count++;
	if (count == pos)
		freetab2(tline, pos);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	**tline;
	char		*line;
	char		*res;
	char		buff[BUFFER_SIZE + 1];
	int			ret;
	int			pos;

	if (fd < 3 && fd != 0)
	{
		freetab(tline);
		return (NULL);
	}
	pos = fd;
	if (fd != 0)
		pos = fd - 2;
	tline = check_fd(tline, pos);
	if (!tline || !tline[pos])
		return (NULL);
	line = tline[pos];
	ret = 1;
	while (ret)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buff[ret] = 0;
		ft_strjoin(&tline[pos], buff, ret);
		res = newline_exist(&tline[pos], tline, pos + 1, 0);
		if (res)
			return (res);
	}
	return (newline_exist(&tline[pos], tline, pos + 1, 1));
}

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
