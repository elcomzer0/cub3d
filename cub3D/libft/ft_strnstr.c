/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:14:18 by miturk            #+#    #+#             */
/*   Updated: 2023/09/06 16:14:20 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*b;
	char	*l;

	if ((!big && len == 0) || (len < ft_strlen(little) && !ft_strlen(big)))
		return (NULL);
	if (!*little && big)
		return ((char *) big);
	b = (char *)big;
	l = (char *)little;
	i = 0;
	j = 0;
	while (b[i] != '\0' && i < len)
	{
		while ((b[i + j] == l[j]) && (b[i + j] != '\0') && (j + i < len))
			j++;
		if (l[j] == '\0')
			return (b + i);
		i++;
		j = 0;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	big[] = "Hello, my name is Miha!";
	char	little[] = "o";
	size_t	len = 3;
	
	printf("%s", ft_strnstr(big, little, len));
	return (0);
}*/
