/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:10:05 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/25 21:54:23 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	**pop_mem(char **src, int msize)
{
	char	**res;
	int		k;

	res = malloc(sizeof(char *) * msize);
	if (res)
	{
		k = -1;
		while (src[++k])
			res[k] = strdup(src[k]);
		while (k < msize - 1)
		{
			res[k] = ft_strdupcpy(NULL, NULL, "", -1);
			k++;
		}
		res[k] = NULL;
	}
	ft_freetab(&src, 1);
	return (res);
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
	buffer = pop_mem(buffer, fd);
	return (buffer);
}

char	*next_line(char ***buffer, int pos)
{
	char	*endl;
	char	*tmp;
	char	*temp;

	endl = ft_strchr((*buffer)[pos], '\n');
	if (!endl)
	{
		tmp = NULL;
		if ((*buffer)[pos][0])
			tmp = strdup((*buffer)[pos]);
		ft_freetab(buffer, 0);
		if (*buffer && (*buffer)[pos])
		{
			free((*buffer)[pos]);
			(*buffer)[pos] = ft_strdupcpy(NULL, NULL, "", -1);
		}
		return (tmp);
	}
	temp = strndup((*buffer)[pos], endl - (*buffer)[pos] + 1);
	tmp = strdup(endl + 1);
	free((*buffer)[pos]);
	(*buffer)[pos] = tmp;
	return (temp);
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
	pos = fd;
	if (fd != 0)
		pos = fd - 2;
	if (!buffer || !buffer[pos])
	{
		ft_freetab(&buffer, 0);
		return (NULL);
	}
	if (!readuntil(buffer + pos, fd))
	{
		ft_freetab(&buffer, 0);
		if (buffer && buffer[pos])
			buffer[pos] = ft_strdupcpy(NULL, NULL, "", -1);
		return (NULL);
	}
	if (!buffer[pos])
	{
		ft_freetab(&buffer, 0);
		return (NULL);
	}
	return (next_line(&buffer, pos));
}
