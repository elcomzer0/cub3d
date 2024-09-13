/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:31:45 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 09:54:14 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)

{
	const unsigned char	*str;
	unsigned char		a;

	str = s;
	a = (unsigned char )c;
	while (0 < n)
	{
		if (*str == a)
			return ((void *)str);
		str++;
		n--;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	s[] = "Hello, my name is";
	size_t	n = 7;
	
	printf("mine: %p\n", ft_memchr(s, 'o', n));
	printf("memchr: %p\n", memchr(s, 'o', n));
	printf("memchr: %s\n", (char *)memchr(s, 'o', n));
	printf("mine: %s\n", (char *)ft_memchr(s, 'o', n));

	return (0);
}*/