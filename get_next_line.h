/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpaulo-p <jpaulo-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 17:12:26 by vneves-c          #+#    #+#             */
/*   Updated: 2026/08/12 00:26:21 by jpaulo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

size_t  ft_strlen(const char *str);
char   *ft_strchr(const char *str, int c);
char   *ft_strjoin(char *stash, char *buffer);
char   *ft_get_line(char *stash);
char   *ft_save_rest(char *stash);

#endif
