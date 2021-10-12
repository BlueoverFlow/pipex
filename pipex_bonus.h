/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:06:15 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/12 18:14:01 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/fcntl.h>
# define ERROR -1
# define BOOL int
# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe_end[2];
	char	**prototype;
	pid_t	id[2];
    BOOL    is_heredoc;
}				t_data;

void	close_fds_and_wait(t_data *data);
int		parser(t_data *data, int argc, char **argv, char **envp);
char	*command_path(t_data *data);

#endif