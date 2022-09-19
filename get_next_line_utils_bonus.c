/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:20 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/15 23:23:22 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	freetab(char **tab)
{
	if (!tab)
		return ;
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

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

void	ft_strjoin(char **line, const char *s1, int bufsize)
{
	char	*res;

	if (bufsize <= 0)
		return ;
	if (*line)
	{
		res = malloc(bufsize + ft_strlen(*line) + 1);
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
	*line = malloc(bufsize + 1);
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
