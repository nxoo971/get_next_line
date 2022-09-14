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

static char	*ft_strndup(const char *s1, size_t len)
{
	char	*res;
	int		i;

	res = malloc(len + 1);
	if (!res)
		return (res);
	i = -1;
	res[len] = 0;
	while (s1[++i] && len-- > 0)
		res[i] = s1[i];
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
			tmp = strdup(endl + 1);
			free(line);
			line = tmp;
			return (res);
		}
	}
	if (line)
	{
		endl = ft_strchr(line, '\n');
		if (!endl)
			tmp = strdup(line);
		else
			tmp = strdup(endl + 1);
		free(line);
		line = NULL;
		return (tmp);
	}
	return (line);
}

int		main(int ac, char **av)
{
	(void)ac;
	char *res;
	int fd = open(av[1], O_RDONLY);
	while ((res = get_next_line(fd)))
		printf("%s", res);
	return (0);
}
