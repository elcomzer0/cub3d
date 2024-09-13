/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:15:52 by miturk            #+#    #+#             */
/*   Updated: 2023/09/06 10:15:54 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	a;
	int				i;

	a = (unsigned char) c;
	i = ft_strlen(s);
	if (a == '\0')
		return ((char *)&s[i]);
	if (s == NULL)
		return (NULL);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char *src = "abbbbbbbb";
	char *d1 = strrchr(src, 'a');
	char *d2 = ft_strrchr(src, 'a');

	if (d1 == d2)
		exit(printf("TEST_SUCCESS"));
	exit(printf("TEST_FAILED"));
	return (0);
}*/
