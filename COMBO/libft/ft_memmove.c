/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 08:25:24 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 10:17:30 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)

{
	int	i;

	i = 0;
	if (dest < src)
	{
		while (i < (int)n)
		{
			((char *)dest)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else if (dest > src)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			((char *)dest)[i] = ((const char *)src)[i];
			i--;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char *src = "this is a good nyancat !\r\n";
	char dst1[0xF0];
	char dst2[0xF0];
	int size = strlen(src);

	memmove(dst1, src, size);
	ft_memmove(dst2, src, size);
	if (!memcmp(dst1, dst2, size))
		exit(printf("test ok"));
	exit(printf("TEST_FAILED"));


	return(0);
}*/
