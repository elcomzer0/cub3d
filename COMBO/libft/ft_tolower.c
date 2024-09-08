/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:16:09 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 11:29:13 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
int	main(void)
{
	printf("%d\n", ft_tolower('A'));
	printf("%d\n", ft_tolower('b'));
	printf("%d\n", ft_tolower(-21));
	printf("%d\n", tolower(-21));
	return(0);
}*/
