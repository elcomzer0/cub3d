/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:34:55 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 11:28:45 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	destlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	j = 0;
	i = 0;
	if ((size == 0 && !dest) || size < ft_strlen(dest))
		return (size + srclen);
	destlen = ft_strlen(dest);
	while (dest[i] != '\0' && i < size)
		i++;
	while (src[j] != '\0' && i + j + 1 < size)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = '\0';
	return (destlen + srclen);
}
/*
int	main(void)
{
	char *str = "the cake is a lie !\0I'm hidden lol\r\n";
	char buff1[0xF00] = "there is no stars in the sky";
	char buff2[0xF00] = "there is no stars in the sky";
	size_t max = strlen("the cake is a lie !\0I'm hidden lol\r\n") + 4;
	size_t r1 = strlcat(buff1, str, max);
	size_t r2 = ft_strlcat(buff2, str, max);

	if (r1 != r2)
		printf("TEST_FAILED");
	char s1[4] = "";
	char s2[4] = "";
	r1 = strlcat(s1, "thx to ntoniolo for this test !", 4)
		;
	r2 = ft_strlcat(s2, "thx to ntoniolo for this test !", 4)
		;
	if (r1 != r2)
		printf("TEST_FAILED");
	printf("TEST_SUCCESS");
	return(0)
}*/
