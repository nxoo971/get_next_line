/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooxn <ooxn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:09 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/21 17:03:46 by ooxn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

char		*get_next_line(int fd);
const char	*ft_strchr(const char *s, int c);
void		ft_strjoin(char **line, const char *s1, int bufsize);
size_t		ft_strlen(const char *s);
void		*freetab(char **buffer, int current);

#endif
