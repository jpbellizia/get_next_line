/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-p <jpaulo-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 00:28:47 by jpaulo-p          #+#    #+#             */
/*   Updated: 2026/08/17 13:29:10 by jpaulo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

size_t	ft_copy(char *dest, char *src, size_t pos)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[pos + i] = src[i];
		i++;
	}
	return (pos + i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	size_t	total_size;
	char	*str;
	size_t	i;

	if (!buffer)
		return (NULL);
	if (!stash)
	{
		stash = malloc(sizeof(char) * 1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	total_size = ft_strlen(stash) + ft_strlen(buffer) + 1;
	str = malloc(sizeof(char) * total_size);
	if (!str)
	{
		free(stash);
		return (NULL);
	}
	i = ft_copy(str, stash, 0);
	i = ft_copy(str, buffer, i);
	str[i] = '\0';
	free(stash);
	return (str);
}

