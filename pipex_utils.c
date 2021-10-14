/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:40:56 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/14 11:43:17 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char	*find_executable(t_data *data, char *path)
{
	char	**tree;
	int		j;

	tree = ft_split(path, ':');
	j = -1;
	while (tree[++j])
	{
		path = ft_strjoin_and_free
			(ft_strjoin(tree[j], "/"), data->prototype[0]);
		if (!access(path, F_OK | X_OK))
		{
			free_2d(tree);
			return (path);
		}
		free(path);
	}
	free_2d(tree);
	return (NULL);
}

void	close_fds_and_wait(t_data *data)
{
	close(data->pipe_end[1]);
	close(data->pipe_end[0]);
	waitpid(-1, NULL, 0);
	waitpid(data->id, NULL, 0);
}

int	parser(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	if (data->argc != 5)
	{
		ft_putstr_fd("please provide 4 paramaters!\n", 2);
		return (-1);
	}
	return (1);
}

int	parser_2(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->is_heredoc = FALSE;
	if (!strcmp(argv[1], "here_doc"))
		data->is_heredoc = TRUE;
	return (1);
}

char	*command_path(t_data *data)
{
	char	*path;
	char	*executable;
	int		j;

	j = 0;
	path = NULL;
	while (data->envp[++j])
	{
		if (!ft_strncmp(data->envp[j], "PATH=", 5))
			path = ft_substr(data->envp[j], 5, ft_strlen(data->envp[j]) - 5);
	}
	if (path)
	{
		executable = find_executable(data, path);
		free(path);
		if (executable)
			return (executable);
	}
	return (data->prototype[0]);
}
