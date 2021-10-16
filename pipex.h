/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:47:52 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/16 18:19:45 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/fcntl.h>
# include <errno.h>
# define ERROR -1
# define BOOL int
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 1

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe_end[2];
	char	**prototype;
	char	*document;
	pid_t	id;
	BOOL	is_heredoc;
	int		exit_status;
	BOOL	path_env;
}			t_data;

void	close_fds_and_wait(t_data *data);
int		parser(t_data *data, int argc, char **argv, char **envp);
int		parser_2(t_data *data, int argc, char **argv, char **envp);
char	*command_path(t_data *data);
int		hundle_heredoc(t_data *data, int i);

#endif
