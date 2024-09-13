/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:45:10 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 11:28:54 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
/*
int	main(void)
{
	char *str = "BBBB";
	char buff1[0xF00];
	char buff2[0xF00];

	memset(buff1, 'A', 20);
	memset(buff2, 'A', 20);
	if (strlcpy(buff1, str, 0) != ft_strlcpy(buff2, str, 0))
		exit(printf("TEST_FAILED"));
	if (!memcmp(buff1, buff2, 20))
		exit(printf("TEST_SUCCESS"));
	for (register int __i = 0; __i < 20; ++__i)
	for (register int __i = 0; __i < 20; ++__i)
	exit(printf("TEST_FAILED"));
}*/