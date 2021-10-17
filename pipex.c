/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:47:52 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/17 14:13:25 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	int	cmd1(t_data *data, int fd)
{
	close(data->pipe_end[0]);
	fd = open(data->argv[1], O_RDONLY);
	if (fd < 3 || is_directory(data->argv[1]))
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
	if (fd < 3 || is_directory(data->argv[1]))
		return (ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ERROR);
	if (dup2(data->pipe_end[0], STDIN_FILENO) == -1)
		return (ERROR);
	close(data->pipe_end[0]);
	close(fd);
	return (1);
}

static	void	call_child(t_data *data, int i)
{
	int		fd[2];
	char	*executable;

	if ((i == 0 && cmd1(data, fd[0]) == ERROR)
		|| (i == 1 && cmd2(data, fd[0]) == ERROR))
	{
		ft_putstr_fd("PIPEX: ", STDERR_FILENO);
		if (i == 0)
			ft_putstr_fd(data->argv[1], STDERR_FILENO);
		else
			ft_putstr_fd(data->argv[4], STDERR_FILENO);
		perror(" ");
		exit(EXIT_FAILURE);
	}
	data->prototype = ft_split(data->argv[i + 2], ' ');
	executable = command_path(data);
	if (execve(executable, data->prototype, data->envp))
		assign_exit_status(data, executable);
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
		data.id = malloc(sizeof(t_id));
		data.id->id = fork();
		if (data.id->id == ERROR)
			return (EXIT_FAILURE);
		ft_lstadd_back(&(data.ids), ft_lstnew(data.id));
		if (data.id->id == 0)
			call_child(&data, i);
	}
	close_fds_and_wait(&data);
	return (data.exit_status);
}
