/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:27:04 by miturk            #+#    #+#             */
/*   Updated: 2023/09/11 10:27:06 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len = len + 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	int				i;
	char			*str;
	long int		num;

	len = ft_length(n);
	i = len - 1;
	num = n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	else if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
	}
	else if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[i--] = (num % 10) + '0';
		num = num / 10;
	}
	str[len] = '\0';
	return (str);
}
/*
int main() {
	int n = -2147483648; 
	char *str;
	str = ft_itoa(n);

	if (str) 
	{
		printf("Integer: %d\n", n);
		printf("String: %s\n", str);
		free(str);
	} 
	else 
	{
		printf("Memory allocation failed.\n");
	}
	return 0;
}*/