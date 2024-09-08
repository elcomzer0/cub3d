/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:07:04 by miturk            #+#    #+#             */
/*   Updated: 2023/09/11 15:07:06 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s2;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	if (s == NULL || f == NULL)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	while (i < len)
	{
		s2[i] = (*f)(i, s[i]);
		i++;
	}
	s2[i] = 0;
	return (s2);
}
/*
char    mycode(unsigned int i, char c)
{
    if (i % 2 == 0)
        return (ft_toupper(c));
    else
        return (ft_tolower(c));
}
int main(void)
{
    char const s[] = "Hello, World!";
    char    *s2 = ft_strmapi(s, mycode);

    printf( "%s\n", s2);
    return (0);
}*/
