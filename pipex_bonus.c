/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:03:55 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/14 12:21:46 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	take_input(t_data *data, int i, int read_end)
{
	int	fd;

	fd = read_end;
	if ((i == 2) || (i == 3 && data->is_heredoc))
	{
		close (read_end);
		if (data->is_heredoc == TRUE)
		{
			if (hundle_heredoc(data, i) == ERROR)
				return (ERROR);
			fd = open("/tmp/.heredoc", O_RDONLY);
		}
		else
			fd = open(data->argv[i - 1], O_RDONLY);
		if (fd < 3)
			return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ERROR);
	close (fd);
	return (1);
}

static	int	give_output(t_data *data, int i)
{
	int	fd;

	fd = data->pipe_end[1];
	if (!data->argv[i + 2])
	{
		close(data->pipe_end[1]);
		if (data->is_heredoc == TRUE)
			fd = open(data->argv[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0666);
		else
			fd = open(data->argv[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
		if (fd < 3)
			return (ERROR);
		close(data->pipe_end[1]);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ERROR);
	close(fd);
	return (1);
}

static	int	call_daughter(t_data *data, int i, int read_end)
{
	char	*path;

	if (take_input(data, i, read_end) == ERROR || give_output(data, i) == ERROR)
		return (ERROR);
	close(read_end);
	data->prototype = ft_split(data->argv[i], ' ');
	if (!data->prototype)
		return (ERROR);
	path = command_path(data);
	if (execve(path, data->prototype, data->envp))
	{
		free(path);
		free_2d(data->prototype);
		return (ERROR);
	}
	return (1);
}

static	int	call_sugar_dady(t_data *data, int i, int read_end)
{
	if (data->argv[i + 1])
	{
		if (data->argv[i + 2] && pipe(data->pipe_end) == ERROR)
			return (ERROR);
		data->id = fork();
		if (data->id == ERROR
			|| (data->id == 0 && call_daughter(data, i, read_end) == ERROR))
			return (ERROR);
		read_end = data->pipe_end[0];
		if (data->argv[++i + 1])
		{
			close(data->pipe_end[1]);
			call_sugar_dady(data, i, read_end);
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;
	int		read_end;

	i = 2;
	read_end = -1;
	if (parser_2(&data, argc, argv, envp) == ERROR)
		return (ERROR);
	if (data.is_heredoc == TRUE)
		i++;
	if (call_sugar_dady(&data, i, read_end) == ERROR)
	{
		perror("error: ");
		return (ERROR);
	}
	close_fds_and_wait(&data);
	return (0);
}
