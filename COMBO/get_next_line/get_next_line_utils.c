/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:13:34 by miturk            #+#    #+#             */
/*   Updated: 2024/08/28 19:10:14 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*get_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s++ == (char)c)
			return ((char *)--s);
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*get_strjoin(char *s1, char *s2)
{
	char	*str3;
	int		i;
	int		j;
	int		k;

	i = get_strlen(s1);
	j = get_strlen(s2);
	k = 0;
	str3 = (char *)malloc(i + j + 1);
	if (str3 == NULL)
		return (free(s2), NULL);
	while (k < i)
	{
		str3[k] = s1[k];
		k++;
	}
	while (k < (i + j))
	{
		str3[k] = s2[k - i];
		k++;
	}
	str3[k] = '\0';
	free(s1);
	return (str3);
}

char	*get_strdup(char *s)
{
	const char	*org;
	char		*dup;
	int			orglen;
	int			i;

	i = 0;
	if (!s || s[0] == '\0')
		return (NULL);
	orglen = get_strlen(s);
	dup = (char *)malloc(sizeof (char) * orglen + 1);
	if (!dup)
		return (0);
	org = s;
	while (org[i] != '\0')
	{
		dup[i] = org[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
