/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:29:12 by miturk            #+#    #+#             */
/*   Updated: 2023/09/05 10:29:14 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}
/*
# define LEN 25
int	main(void)
{
	char arr[LEN]= "Hello World!";
	int	i;
	i = 0;
	while(i < LEN)
	{
		printf("%c", arr[i]);
		i++;
	}
	printf("\n");
	ft_memset(arr+3, 'f', LEN-2);
	i = 0;
	while(i < LEN)
	{
		printf("%c", arr[i]);
		i++;
	}
	return(0);
}
*/
