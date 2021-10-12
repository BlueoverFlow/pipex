/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 08:50:03 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/11 11:35:02 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 100

# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

int		get_next_line(int fd, char **line);
char	*is_str2(size_t size);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strchr2(const char *s, int c);
int		get_buffer(char **buffer, char *reader, int fd, int *ret);
char	*get_line(char **buffer);

#endif
