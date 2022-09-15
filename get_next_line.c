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

char	*get_next_line(int fd)
{
	static char	*line;
	char		*endl;
	char		*tmp;
	char		*res;
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 3 && fd != 0)
		return (NULL);
	ret = 1;
	while (ret)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buff[ret] = 0;
		ft_strjoin(&line, buff, ret);
		endl = ft_strchr(line, '\n');
		if (endl)
		{
			res = ft_strndup(line, (endl - line) + 1);
			tmp = ft_strndup(endl + 1, -1);
			free(line);
			line = tmp;
			return (res);
		}
	}
	if (!line)
		return (line);
	if (line && !*line)
	{
		free(line);
		line = NULL;
		return (line);
	}
	endl = ft_strchr(line, '\n');
	if (!endl)
		tmp = ft_strndup(line, -1);
	else
		tmp = ft_strndup(endl + 1, -1);
	free(line);
	line = NULL;
	return (tmp);
}
/*
int		main(int ac, char **av)
{
	(void)ac;
	char *res;
	int fd = open(av[1], O_RDONLY);
	while ((res = get_next_line(fd)))
		printf("%s", res);
	return (0);
}*/
