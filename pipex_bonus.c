/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:03:55 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/12 18:25:03 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	if (parser(&data, argc, argv, envp) == ERROR
		|| pipe(data.pipe_end) == ERROR)
	{
		perror("error: ");
		return (ERROR);
	}
	while (++i < 2)
	{
		data.id[i] = fork();
		if (data.id[i] == ERROR || (data.id[i] == 0
				&& call_child(&data, i) == ERROR))
		{
			perror("error: ");
			return (ERROR);
		}
	}
	return (0);
}
