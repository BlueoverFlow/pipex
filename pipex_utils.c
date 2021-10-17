/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:40:56 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/17 14:12:41 by ael-mezz         ###   ########.fr       */
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
		if (!access(path, F_OK))
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
	int		stat;
	t_list	*tmp;

	close(data->pipe_end[1]);
	close(data->pipe_end[0]);
	while (data->ids)
	{
		data->id = data->ids->content;
		waitpid(data->id->id, &stat, 0);
		if (WIFEXITED(stat))
			data->exit_status = WEXITSTATUS(stat);
		tmp = data->ids->next;
		free(data->id);
		free(data->ids);
		data->ids = tmp;
	}
}

int	parser(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	if (data->argc != 5)
	{
		ft_putstr_fd("use :\"./pipex file1 cmd1 cmd2 file2\"\n", 2);
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
	if (data->argc < 5)
	{
		ft_putstr_fd("use :\"./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\"\n", 2);
		ft_putstr_fd("Try to add \"here_doc\" as first parameter ", 2);
		ft_putstr_fd("to support \"<<\" and \">>\"!\n", 2);
		return (-1);
	}
	if (!ft_strcmp("here_doc", data->argv[1]))
	{
		data->is_heredoc = TRUE;
		if (data->argc < 6)
		{
			ft_putstr_fd("use: \"./pipex here_doc LIMITER ", 2);
			ft_putstr_fd("cmd1 cmd2 cmd3 ... cmdn file\"!\n", 2);
			return (-1);
		}
	}
	return (1);
}

char	*command_path(t_data *data)
{
	char	*path;
	char	*executable;
	int		j;

	j = 0;
	path = NULL;
	data->path_env = FALSE;
	while (data->envp[++j])
	{
		if (!ft_strncmp(data->envp[j], "PATH=", 5))
			path = ft_substr(data->envp[j], 5, ft_strlen(data->envp[j]) - 5);
	}
	if (path)
	{
		data->path_env = TRUE;
		executable = find_executable(data, path);
		free(path);
		if (executable)
			return (executable);
	}
	return (data->prototype[0]);
}
