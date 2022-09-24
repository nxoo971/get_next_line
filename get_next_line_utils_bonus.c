/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:20 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/24 23:04:49 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

const char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	while (*s && *s != ch)
		s++;
	if (*s == ch)
		return (s);
	return (NULL);
}

char	*ft_strcpy(char *dst, const char *src)
{
	char	*start;

	start = dst;
	while (*src)
		*start++ = *src++;
	*start = 0;
	return (dst);
}

void	ft_freetab(char ***ptr, int force)
{
	int		i;
	int		res;

	if (!*ptr)
		return ;
	i = -1;
	res = 0;
	while (!force && (*ptr)[++i] != NULL)
	{
		if ((*ptr)[i][0] != '\0')
			res++;
	}
	if (res == 0)
	{
		i = -1;
		while ((*ptr)[++i] != NULL)
		{
			free((*ptr)[i]);
			(*ptr)[i] = NULL;
		}
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_strjoin(char **line, const char *s1, int size)
{
	char	*res;
	int		i;

	if (*line && **line)
	{
		i = 0;
		while ((*line)[i])
			i++;
		res = malloc(size + i + 1);
		if (res)
		{
			ft_strcpy(res, *line);
			ft_strcpy(res + i, s1);
			free(*line);
			*line = res;
		}
		return ;
	}
	if (*line && !**line)
		free(*line);
	*line = malloc(size + 1);
	if (*line)
		ft_strcpy(*line, s1);
}

int	readuntil(char **bufferline, int fd)
{
	char	buff[BUFFER_SIZE + 1];
	int		byteread;

	byteread = 1;
	while (byteread)
	{
		byteread = read(fd, buff, BUFFER_SIZE);
		if (byteread < 0)
			return (0);
		buff[byteread] = 0;
		if (byteread == 0)
			break ;
		ft_strjoin(bufferline, buff, byteread);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (1);
}
