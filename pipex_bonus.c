/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:03:55 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/17 14:13:46 by ael-mezz         ###   ########.fr       */
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

static	void	call_daughter(t_data *data, int i, int read_end)
{
	char	*executable;

	if (take_input(data, i, read_end) == ERROR || give_output(data, i) == ERROR)
	{
		perror("PIPEX: the argument");
		exit(1);
	}
	close(read_end);
	data->prototype = ft_split(data->argv[i], ' ');
	executable = command_path(data);
	if (execve(executable, data->prototype, data->envp))
		assign_exit_status(data, executable);
}

static	int	call_sugar_dady(t_data *data, int i, int read_end)
{
	if (data->argv[i + 1])
	{
		if (data->argv[i + 2] && pipe(data->pipe_end) == ERROR)
			return (ERROR);
		data->id = malloc(sizeof(t_id));
		data->id->id = fork();
		if (data->id->id == ERROR)
			return (ERROR);
		ft_lstadd_back(&(data->ids), ft_lstnew(data->id));
		if (data->id->id == 0)
			call_daughter(data, i, read_end);
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
	return (data.exit_status);
}
