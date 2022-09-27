/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nxoo <nxoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 23:23:09 by ooxn              #+#    #+#             */
/*   Updated: 2022/09/28 00:34:12 by nxoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strdupcpy(char *d1, char *s1, char *s2, int n);
char	*ft_strchr(const char *s, int c);
int		readuntil(char **bufferline, int fd);
void	ft_freetab(char ***ptr, int force);

#endif
