/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:10:54 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/14 20:10:57 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

char		*get_next_line(int fd);
const char	*ft_strchr(const char *s, int c);
void		ft_strjoin(char **line, const char *s1, int bufsize);
size_t		ft_strlen(const char *s);

#endif
