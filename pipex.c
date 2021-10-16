/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:47:52 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/16 18:57:58 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	cmd1(t_data *data, int fd)
{
	close(data->pipe_end[0]);
	fd = open(data->argv[1], O_RDONLY);
	if (fd < 3)
		return (ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ERROR);
	if (dup2(data->pipe_end[1], STDOUT_FILENO) == -1)
		return (ERROR);
	close(data->pipe_end[1]);
	close(fd);
	return (1);
}

static	int	cmd2(t_data *data, int fd)
{
	close(data->pipe_end[1]);
	fd = open(data->argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 3)
		return (ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ERROR);
	if (dup2(data->pipe_end[0], STDIN_FILENO) == -1)
		return (ERROR);
	close(data->pipe_end[0]);
	close(fd);
	return (1);
}

static void assign_exit_status(t_data *data, char *executable)
{
	ft_putstr_fd("PIPEX: ", STDERR_FILENO);
	ft_putstr_fd(data->prototype[0], STDERR_FILENO);
	if ((errno == ENOENT) && (executable[0] == '~' || executable[0] == '.'
		|| executable[0] == '/'))
	{
		perror(" ");
		exit(127);
	}
	else if (errno == EACCES) //need to check if its a directory
	{
		perror(" ");
		exit(126);
	}
	else if (errno == ENOENT)
	{
		if (!data->path_env)
		{
			errno = ENOENT;
			perror(" ");
		}
		else
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
}

static	void	call_child(t_data *data, int i)
{
	int		fd[2];
	char	*executable;

	if ((i == 0 && cmd1(data, fd[0]) == ERROR)
		|| (i == 1 && cmd2(data, fd[0]) == ERROR))
	{
		perror("PIPEX: ");
		exit (EXIT_FAILURE);
	}
	data->prototype = ft_split(data->argv[i + 2], ' ');
	executable = command_path(data);
	if (execve(executable, data->prototype, data->envp))
	{
		assign_exit_status(data, executable);
		if (ft_strcmp(executable, data->prototype[0]))
			free(executable);
		free_2d(data->prototype);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	i = -1;
	if (parser(&data, argc, argv, envp) == ERROR)
		exit(EXIT_FAILURE);
	if (pipe(data.pipe_end) == ERROR)
	{
		perror("PIPEX: ");
		return (EXIT_FAILURE);
	}
	while (++i < 2)
	{
		data.id = fork();
		if (data.id == ERROR)
			return (EXIT_FAILURE);
		else if (data.id == 0)
			call_child(&data, i);
	}
	close_fds_and_wait(&data);
	return (data.exit_status);
}
