/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:10:05 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/24 21:28:47 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	**popmem(char **src, int msize)
{
	char	**res;
	int		i;
	int		k;

	i = 0;
	res = malloc(sizeof(char *) * msize);
	if (res)
	{
		k = -1;
		while (src[++k])
			res[k] = strdup(src[k]);
		while (k < msize - 1)
		{
			res[k] = strdup("");
			k++;
		}
		res[k] = NULL;
	}
	ft_freetab(&src, 1);
	return (res);
}

char	**create_buffer(char **buffer, int fd)
{
	int		size;

	size = fd;
	if (fd == 0)
		size = 2;
	buffer = malloc(sizeof(char *) * size);
	if (buffer)
	{
		buffer[--size] = 0;
		while (--size >= 0)
		{
			buffer[size] = malloc(1);
			if (!buffer[size])
			{
				ft_freetab(&buffer, 1);
				return (NULL);
			}
			buffer[size][0] = '\0';
		}
	}
	return (buffer);
}

char	**check_line_by_fd(char **buffer, int fd)
{
	int		pos;

	if (!buffer)
	{
		buffer = create_buffer(buffer, fd);
		if (!buffer)
			return (NULL);
	}
	pos = fd;
	if (fd != 0)
		pos = fd - 2;
	if (buffer[pos] != NULL)
		return (buffer);
	buffer = popmem(buffer, fd);
	return (buffer);
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

char	*get_next_line(int fd)
{
	static char		**buffer;
	int				pos;

	if (fd < 3 && fd != 0)
	{
		ft_freetab(&buffer, 1);
		return (NULL);
	}
	buffer = check_line_by_fd(buffer, fd);
	pos = (!fd ? fd : fd - 2);
	if (!buffer || !buffer[pos])
	{
		ft_freetab(&buffer, 0);
		return (NULL);
	}
	if (!readuntil(buffer + pos, fd))
	{
		ft_freetab(&buffer, 0);
		if (buffer && buffer[pos])
			buffer[pos] = strdup("");
		return (NULL);
	}
	return (next_line(&buffer, pos));
}
