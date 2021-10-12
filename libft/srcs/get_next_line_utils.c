/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:52:45 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/11 11:29:51 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*is_str2(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strndup(const char *s, size_t n)
{
	unsigned int	i;
	char			*cpy;

	cpy = (char *)malloc(sizeof(*cpy) * (n + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (*s && i < n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strchr2(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	if (!s)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (c == '\0')
		return (str);
	else
		return (NULL);
}
