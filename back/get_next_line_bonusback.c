/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:10:44 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/20 20:41:12 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		dst[i] = ft_strdup(src[i]);
	return (dst);
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

char	**check_line_by_fd(char	**tline, int fd)
{
	char	**res;
	int		size;
	int		i;
	int		ret;

	if (!tline)
	{
		size = fd;
		if (fd == 0)
			size = 2;
		tline = malloc(sizeof(char *) * size);
		if (tline)
		{
			i = 0;
			while (i < (size - 1))
			{
				tline[i] = malloc(1);
				tline[i][0] = '\0';
				i++;
			}
			tline[i] = 0;
		}
		return (tline);
	}
	int pos = fd - 2;
	if (fd == 0)
		pos = 0;
	if (tline[pos])
	{
		if (tline[pos][0])
			return (tline);
		char buff[BUFFER_SIZE + 1];
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret <= 0)
		{
			freetab(tline);
			return (NULL);
		}
		buff[ret] = 0;
		ft_strjoin(&tline[pos], buff, ret);
		return (tline);
	}
	res = arraydup(tline);
	freetab(tline);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	**tline;
	char		*res;
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 3 && fd != 0)
	{
		//freetab(tline);
		return (NULL);
	}
	int pos = fd - 2;
	if (fd == 0)
		pos = 0;
	ret = 1;
	tline = check_line_by_fd(tline, fd);
	if (!tline)
		return (NULL);
	ret = 1;
	while (ret)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buff[ret] = 0;
		ft_strjoin(tline + pos, buff, ret);
		res = newline_exist(tline + pos, 0);
		if (res)
			return (res);
	}
	return (newline_exist(tline + pos, 1));
}
