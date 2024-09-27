/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:32:19 by miturk            #+#    #+#             */
/*   Updated: 2024/09/22 11:20:12 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*result;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	while (*s1 != '\0' && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	result = ft_substr(s1, 0, len);
	if (!result)
		return (NULL);
	return (result);
}

// int	main(void) // \t\t\n \nsomestring\n  \t -> somestring
// {
// 	char s1[] = "  hello i may have   ";
// 	char set[] = " "; // Define the set of characters to trim
// 	char *trim = ft_strtrim(s1, set);
// 	printf("%s\n", trim);
// 	return (0);
// }