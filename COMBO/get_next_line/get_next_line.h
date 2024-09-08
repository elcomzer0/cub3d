/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:14:01 by miturk            #+#    #+#             */
/*   Updated: 2024/08/29 17:29:36 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1042
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <stddef.h>

char	*get_strchr(char *s, int c);
size_t	get_strlen(char *s);
char	*get_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*get_read_from_file_to_buffer(int fd, char **line_buffer);
char	*get_clean_buffer(char **line_buffer);
char	*get_read_from_buffer_newline(char **line_buffer);
char	*get_strdup(char *s);

#endif
