/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:30:19 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 09:54:31 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)

{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = s1;
	str2 = s2;
	while (n-- > 0)
	{
		if (*str1 != *str2)
			return ((*str1 - *str2));
		str1++;
		str2++;
	}
	return (0);
}
/*
int	main(void)
{
	char	s1[]="Hella";
	char	s2[]="Hell";
	size_t	n = 5;
	printf("%d\n",ft_memcmp(s1, s2, n));
	printf("%d\n", memcmp(s1, s2, n));
	return(0);
}*/
