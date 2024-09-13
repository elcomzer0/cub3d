/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:23:23 by miturk            #+#    #+#             */
/*   Updated: 2024/08/31 10:16:20 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s++ == (char)c)
			return ((char *)--s);
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

// int	main(void)
// {
// 	char	s[] = "Hello, my name is";
// 	printf("%s\n", ft_strchr(s, 'o'));
// 	printf("%s\n", strchr(s, 'o'));
// 	return (0);
// }
