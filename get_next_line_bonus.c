/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:10:05 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/24 01:03:14 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int		ft_isfreeable(char **ptr, int msize)
{
	int		i;
	int		res;
(void)msize;
	i = 0;
	res = 0;
	while (ptr[i] != NULL)
	{
		if (ptr[i][0] != '\0')
			res++;
		i++;
	}
	return (res == 0);
}

void	ft_freetab(char **ptr, int msize)
{
	int	i;
(void)msize;
	if (!ptr)
		return ;
	i = 0;
	while (ptr[i] != NULL)
	{
		ft_free(ptr + i);
		i++;
	}
	free(ptr);
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
	ft_freetab(src, msize);
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
				ft_freetab(buffer, fd);
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

int		readuntil(char **bufferline, int fd)
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
		if (strchr(buff, '\n'))
			break ;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char		**buffer;
	char			*endl;
	char			*tmp;
	char			*temp;
	int				pos;

	if (fd < 3 && fd != 0)
	{
		ft_freetab(buffer, fd);
		buffer = NULL;
		return (NULL);
	}
	buffer = check_line_by_fd(buffer, fd);
	pos = (!fd ? fd : fd - 2);
	if (!buffer || !buffer[pos])
	{
		if (ft_isfreeable(buffer, fd))
		{
			ft_freetab(buffer, fd);
			buffer = NULL;
		}
		return (NULL);
	}
	if (!readuntil(buffer + pos, fd))
	{
		if (ft_isfreeable(buffer, fd))
		{
			ft_freetab(buffer, fd);
			buffer = NULL;
			return (NULL);
		}
		/*if (buffer[pos] != NULL)
			ft_free(buffer + pos);*/
		buffer[pos] = strdup("");
		return (NULL);
	}
	if (!buffer[pos])
	{
		if (ft_isfreeable(buffer, fd))
		{
			ft_freetab(buffer, fd);
			buffer = NULL;
		}
		return (NULL);
	}
	endl = strchr(buffer[pos], '\n');
	if (!endl)
	{
		tmp = NULL;
		if (buffer[pos][0]) // si il y a quand même qqchose, tout free et return la line
			tmp = strdup(buffer[pos]);
		if (ft_isfreeable(buffer, fd))
		{
			ft_freetab(buffer, fd);
			buffer = NULL;
			return (NULL);
		}
		if (buffer[pos])
			ft_free(buffer + pos);
		buffer[pos] = strdup("");
		return (tmp);
	}
	temp = strndup(buffer[pos], endl - buffer[pos] + 1);
	if (temp)
	{
		tmp = strdup(endl + 1);
		ft_free(buffer + pos);
		buffer[pos] = tmp;
	}
	return (temp);
}