/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 08:00:29 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/17 13:52:23 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_directory(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd >= 3)
	{
		close (fd);
		errno = EISDIR;
		return (1);
	}
	return (0);
}

static void	free_executable_and_exit(t_data *data, char *executable, int exitt)
{
	if (ft_strcmp(executable, data->prototype[0]))
		free(executable);
	free_2d(data->prototype);
	perror(" ");
	exit(exitt);
}

void	assign_exit_status(t_data *data, char *executable)
{
	ft_putstr_fd("PIPEX: ", STDERR_FILENO);
	ft_putstr_fd(data->prototype[0], STDERR_FILENO);
	if ((errno == ENOENT) && (executable[0] == '~' || executable[0] == '.'
			|| executable[0] == '/'))
		free_executable_and_exit(data, executable, 127);
	else if (errno == ENOENT)
	{
		if (!data->path_env)
		{
			errno = ENOENT;
			free_executable_and_exit(data, executable, 127);
		}
		else
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	else if (is_directory(executable) || errno == EACCES)
		free_executable_and_exit(data, executable, 126);
}
