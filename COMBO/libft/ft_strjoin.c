/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:59:25 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 11:28:38 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str3;
	int		i;
	int		j;
	int		k;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	str3 = (char *)malloc(i + j + 1);
	if (str3 == NULL)
		return (NULL);
	while (k < i)
	{
		str3[k] = s1[k];
		k++;
	}
	while (k < (i + j))
	{
		str3[k] = s2[k - i];
		k++;
	}
	str3[k] = '\0';
	return (str3);
}
/*
int	main(void)
{
	char const s1[] = "Hello, ";
	char const s2[] = "World!";
	printf("%s", ft_strjoin(s1, s2));
	return (0);
}*/
