/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:47:37 by miturk            #+#    #+#             */
/*   Updated: 2024/09/03 10:15:06 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '+' || nptr[i] == '-' || nptr[i] == '0')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
		if ((nptr[i] == '+') || (nptr[i] == '-'))
			return (0);
	}
	while (nptr[i] != '\0')
	{
		if (ft_isdigit(nptr[i]) == 0)
			return (-1);
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}
/*
int	main(void)
{
	const char	nptr[] = " +--123abc";
	printf("%d\n", ft_atoi(nptr));
	printf("%d", atoi(nptr));
	return(0);
}*/
