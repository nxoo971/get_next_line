/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:20 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/24 21:29:16 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strcat(char *dst, const char *src)
{
	char	*start;

	start = dst;
	while (*start)
		start++;
	while (*src)
		*start++ = *src++;
	*start = 0;
	return (dst);
}

void	ft_strjoin(char **line, const char *s1, int size)
{
	char	*res;

	if (size <= 0)
		return ;
	if (*line && **line)
	{
		res = malloc(size + ft_strlen(*line) + 1);
		if (res)
		{
			*res = 0;
			ft_strcat(res, *line);
			ft_strcat(res, s1);
			free(*line);
			*line = res;
		}
		return ;
	}
	if (*line && !**line)
		free(*line);
	*line = malloc(size + 1);
	if (*line)
	{
		**line = 0;
		ft_strcat(*line, s1);
	}
}

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

char	*next_line(char ***buffer, int pos)
{
	const char		*endl;
	char			*tmp;
	char			*temp;

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
			(*buffer)[pos] = strdup("");
		}
		return (tmp);
	}
	temp = strndup((*buffer)[pos], endl - (*buffer)[pos] + 1);
	if (temp)
	{
		tmp = strdup(endl + 1);
		free((*buffer)[pos]);
		(*buffer)[pos] = tmp;
	}
	return (temp);
}
