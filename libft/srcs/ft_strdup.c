/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 11:18:02 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/06/07 18:14:40 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	int		i;

	if (!s1)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(s1) + 1);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	new[i] = '\0';
	return (new);
}
