/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:54:41 by brmaria-          #+#    #+#             */
/*   Updated: 2025/05/23 10:58:45 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef FD
#  define FD 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*handle_nl(char *buffer, char *line);
char	*read_stash(char *buffer, char *line, int fd);
char	*ft_strjoin_free(char *line, char *buffer);
void	ft_memmove(char *buffer);
ssize_t	ft_strchr(char *s);
size_t	ft_strlen(char *c);

#endif