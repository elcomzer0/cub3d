/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:16:50 by miturk            #+#    #+#             */
/*   Updated: 2023/09/06 14:45:08 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*cdest;
	char	*csrc;
	size_t	i;

	cdest = (char *) dest;
	csrc = (char *) src;
	if (src == NULL && dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "This is gonna get copied";
	char	dest[50];
	char	*dest_ptr = ft_memcpy(dest, src, ft_strlen(src) + 1);
	
	printf("src: %s\n", src);
	printf("dest: %s\n", dest);
	printf("dest_ptr: %p\n", dest_ptr);
	printf("dest: %p\n", dest);
	return (0);
}*/
