/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-p <jpaulo-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 00:28:47 by jpaulo-p          #+#    #+#             */
/*   Updated: 2026/08/12 02:28:21 by jpaulo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t  ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

char   *ft_strchr(const char *str, int c)
{
	int	i;

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

char   *ft_strjoin(char *stash, char *buffer)
{
	size_t	total_size;
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
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
	str = malloc(sizeof(char) * 1 * total_size);
	if (!str)
	{
		free(stash);		
		return (NULL);
	}
	while (stash[i] != '\0')
	{
		str[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j] != '\0')
	{
		str[i + j] = buffer[j];
		j++;
	}
	str[i + j] = '\0';
	free(stash);
	return (str);
}
