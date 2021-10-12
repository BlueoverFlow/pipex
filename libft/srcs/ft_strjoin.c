/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mezz <ael-mezz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:53:26 by ael-mezz          #+#    #+#             */
/*   Updated: 2021/10/11 11:36:25 by ael-mezz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*nstr;

	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	nstr = (char *)malloc(sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + 1));
	if (!nstr)
		return (NULL);
	nstr = ft_strcpy(nstr, s1);
	return (ft_strcat(nstr, s2));
}

char	*ft_strjoin_and_free(char *s1, char const *s2)
{
	char	*nstr;

	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	nstr = (char *)malloc(sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + 1));
	if (!nstr)
		return (NULL);
	nstr = ft_strcpy(nstr, s1);
	free(s1);
	return (ft_strcat(nstr, s2));
}
