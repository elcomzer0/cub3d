/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 09:55:01 by miturk            #+#    #+#             */
/*   Updated: 2024/09/18 16:39:47 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static size_t	ft_strplace(const char *s, char c, size_t n)
{
	while (s[n] != '\0' && s[n] != c)
		n++;
	return (n);
}

char	**ft_split(char const *s, char c)
{
	char		**lst;
	size_t		n;
	size_t		i;

	i = 0;
	n = 0;
	lst = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!s || !lst)
		return (NULL);
	while (i < ft_count(s, c))
	{
		while (s[n] == c)
			n++;
		lst[i] = ft_substr(s, n, ft_strplace(s, c, n) - n);
		if (!lst[i++])
		{
			while (i > 0)
				free(lst[--i]);
			free(lst);
			return (NULL);
		}
		n = ft_strplace(s, c, n) + 1;
	}
	lst[i] = NULL;
	return (lst);
}
/*
int	main()
{
	char const	*s = "Hello this is a test string";
	char	c = ' ';
	int	i = 0;

	char **lst;
	lst = ft_split(s, c);
	if (lst)
	{
		while(lst[i])
		{
			printf("%s\n", lst[i]);
			i++;
		}
	}
	free(lst);
	
	
	return (0);
}*/
