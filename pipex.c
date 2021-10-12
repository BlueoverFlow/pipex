/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:47:52 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/12 16:52:04 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex.h"

static int cmd1(t_data *data, int fd)
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

static int cmd2(t_data *data, int fd)
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

static int call_child(t_data *data, int i)
{
    int     fd[2];

    if ((i == 0 && cmd1(data, fd[0]) == ERROR) || (i == 1 && cmd2(data, fd[0]) == ERROR))
        return (ERROR);
    data->prototype = ft_split(data->argv[i + 2], ' ');
    if (!data->prototype)
        return (ERROR);
    if (execve(command_path(data), data->prototype, data->envp))
        return (ERROR);
    return (1);
}



int main(int argc, char **argv, char **envp)
{
    t_data  data;
    int     i;

    i = -1;
    if (parser(&data, argc, argv, envp) == ERROR || pipe(data.pipe_end) == ERROR)
    {
        perror("error: ");
        return (ERROR);
    }
    while (++i < 2)
    {
        if ((data.id[i] = fork()) == ERROR ||  (data.id[i] == 0 && call_child(&data, i) == ERROR))
        {
            perror("error: ");
            return (ERROR);
        }
    }
    return (0);
}