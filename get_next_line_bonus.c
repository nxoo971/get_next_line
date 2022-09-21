#include "get_next_line_bonus.h"

void	*freetab(char **buffer, int current)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (buffer[i])
	{
		if (buffer[i][0] != 0)
			count++;
		i++;
	}
	if (count == 0)
	{
		i = -1;
		while (buffer[++i])
			free(buffer[i]);
		free(buffer);
		buffer = NULL;
	}
	else
	{
		free(buffer[current]);
		buffer[current] = malloc(1);
		buffer[current][0] = 0;
	}
	return (buffer);
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
		dst[i] = strdup(src[i]);
	return (dst);
}

char	**get_line_by_fd(int fd, char **buffer)
{
	char	**res;
	int		size;

	if (!buffer)
	{
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
					return (freetab(buffer, 0));
				buffer[size][0] = '\0';
			}
		}
		return (buffer);
	}
	if (buffer[fd == 0 ? fd : fd - 2])
		return (buffer);
	res = arraydup(buffer);
	freetab(buffer, 0);
	return (res);
}

int		readuntil(int fd, char **bufferline)
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
	static char	**buffer;
	char		*temp;
	char		*tmp;
	char		*endl;
	int			pos;

	if (fd < 3 && fd != 0)
		return (freetab(buffer, 0));
	buffer = get_line_by_fd(fd, buffer);
	pos = (fd == 0 ? fd : fd - 2);
	if (!buffer || !buffer[pos])
		return (NULL);
	if (!readuntil(fd, buffer + pos))
		return (NULL);
	endl = strchr(buffer[pos], '\n');
	if (!endl)
	{
		tmp = NULL;
		if (buffer[pos][0])
			tmp = strdup(buffer[pos]);
		freetab(buffer, pos);
		return (tmp);
	}
	temp = strndup(buffer[pos], endl - buffer[pos] + 1);
	if (temp)
	{
		tmp = strdup(endl + 1);
		free(buffer[pos]);
		buffer[pos] = tmp;
	}
	return (temp);
}
