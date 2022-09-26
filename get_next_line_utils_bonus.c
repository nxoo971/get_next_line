/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:20 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/25 21:53:22 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if ((char)*s == (char)c)
		return ((char *)s);
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

char	*ft_strdupcpy(char *d1, char *s1, char *s2, int n)
{
	char	*res;
	int		i;

	if (!s2)
	{
		i = 0;
		if (n != -1)
		{
			while (i < n && s1[i])
			{
				d1[i] = s1[i];
				i++;
			}
		}
		else
		{
			while (s1[i])
			{
				d1[i] = s1[i];
				i++;
			}
		}
		d1[i] = 0;
		return (d1);
	}
	if (n == -1)
	{
		i = 0;
		while (s2[i])
			i++;
		res = malloc(i + 1);
		res[i] = 0;
		while (--i >= 0 || s2[i])
			res[i] = s2[i];
		return (res);
	}
	i = n;
	res = malloc(i + 1);
	res[i] = 0;
	while (--i >= 0 && s2[i])
		res[i] = s2[i];
	return (res);
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
			//ft_strdupcpy(res, *line, NULL, -1);
			//ft_strdupcpy(res + i, (char *)s1, NULL, -1);
			ft_strcpy(res, *line);
			ft_strcpy(res + i, s1);
			free(*line);
			*line = res;
		}
		return ;
	}
	if (*line && !**line)
		free(*line);
	*line = strdup(s1);
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
