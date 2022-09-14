/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:47:57 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/14 16:47:58 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void *free_buff(void *buff)
{
    if (buff)
    {
        free(buff);
        buff = NULL;
    }
    return (NULL);
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

static char *ft_strdupcat(const char *s1, int bufsize, char *line)
{
    char    *res;
    size_t  size;

    if (!line)
        size = 0;
    else
        size = ft_strlen(line);
    res = malloc(bufsize + size + 1);
    if (!res)
        return (res);
    *res = 0;
    if (line)
        ft_strcat(res, line);
    ft_strcat(res, s1);
    return (res);
}

static char *ft_strndup(const char *s1, size_t len)
{
    char    *res;
    int     i;

    res = malloc(len + 1);
    if (!res)
        return (res);
    i = -1;
    res[len] = 0;
    while (s1[++i] && len-- > 0)
        res[i] = s1[i];
    return (res);
}

char        *get_next_line(int fd)
{
    static char *line;
    char        *endl;
    char        *res;
    char        buff[BUFFER_SIZE + 1];
    int         ret;

    if (fd < 0)
        return (NULL);
    ret = 1;
    while (ret)
    {
        ret = read(fd, buff, BUFFER_SIZE);
        if (ret < 0)
            return (free_buff(line));
        buff[ret] = 0;
        if (ret > 0)
            line = ft_strdupcat(buff, ret, line);
        endl = ft_strchr(line, '\n');
        if (endl)
        {
            res = ft_strndup(line, endl - line);
            line = endl + 1;
            return (res);
        }
    }
    return (NULL);
}

int     main(void)
{
    int fd = open("get_next_line_bonus.c", O_RDONLY);
    if (fd == -1)
        printf("can't open fd");
    else {
        char *res;
        while ((res = get_next_line(fd)))
            printf("%s\n", res);
    }
    return (0);
}