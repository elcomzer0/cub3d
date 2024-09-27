/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:13:45 by miturk            #+#    #+#             */
/*   Updated: 2024/09/18 18:03:19 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)

{
	const char	*org;
	char		*dup;
	int			orglen;
	int			i;

	i = 0;
	orglen = ft_strlen(s);
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
/*
int	main(void)
{
	char	s[] = "Hello, World!";
	char	*duplicate;
	int	 orglen;
	int	duplen;

	duplicate = ft_strdup(s);
	orglen = ft_strlen(s);
	duplen = ft_strlen(duplicate);
	
	printf("Original: '%s' (%d)\n", s, orglen);
	printf("Copy: '%s' (%d)\n", duplicate, duplen);
	return (0);
}*/
