/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:56:14 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/14 12:22:16 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_tmp(char *tmp, char **line, char **rest, char *buf)
{
	char	*tp;

	*tmp = '\0';
	*line = ft_strdup(*rest);
	if (!*line)
		return (-1);
	tp = *rest;
	*rest = ft_strdup(tmp + 1);
	if (!*rest)
		return (-1);
	free(tp);
	free(buf);
	return (1);
}

int	checkrest(char **rest, char **line)
{
	char	*tp;
	char	*tmp;

	if (*rest)
	{
		tmp = ft_strchr(*rest, '\n');
		if (tmp)
		{
			*tmp = '\0';
			*line = ft_strdup(*rest);
			if (!*line)
				return (-1);
			tp = *rest;
			*rest = ft_strdup(tmp + 1);
			if (!*rest)
				return (-1);
			free(tp);
			return (1);
		}
	}
	else
		*rest = ft_strdup("");
	return (0);
}

int	getn(int fd, char **rest, char *buf, char **line)
{
	int		r;
	char	*tmp;

	r = read(fd, buf, BUFFER_SIZE);
	while (r > 0)
	{
		buf[r] = '\0';
		*rest = ft_strjoin_and_free(*rest, buf);
		if (!*rest)
			return (-1);
		tmp = ft_strchr(*rest, '\n');
		if (tmp)
			return (ft_check_tmp(tmp, line, rest, buf));
		ft_bzero(buf, BUFFER_SIZE);
		r = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (r);
}

int	get_next_line(int fd, char **line)
{
	int			rd;
	static char	*rest[1024];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE < 0 || !line)
		return (-1);
	rd = checkrest(rest + fd, line);
	if (rd)
		return (rd);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (-1);
	rd = getn(fd, rest + fd, buf, line);
	if (rd == 1)
		return (1);
	if (*(rest + fd) && !rd)
	{
		*line = ft_strdup(*(rest + fd));
		if (!*line)
			return (-1);
		free(*(rest + fd));
		*(rest + fd) = NULL;
	}
	return (rd);
}

int	hundle_heredoc(t_data *data, int i)
{
	int		fd;
	char	*file_name;
	char	*input;

	file_name = ft_strdup("/tmp/.heredoc");
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 3)
	{
		free(file_name);
		return (ERROR);
	}
	while (1)
	{
		ft_putstr_fd("> ", STDERR_FILENO);
		get_next_line(STDIN_FILENO, &input);
		if (!ft_strcmp(data->argv[i - 1], input))
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	close (fd);
	return (1);
}
