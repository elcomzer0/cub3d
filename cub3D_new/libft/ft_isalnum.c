/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:34:36 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 09:49:07 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (8);
	return (0);
}
/*
int	main(void)
{
	int	i;
	i = 65;
	
	printf("%d\n", isalnum(i));
	printf("%d", ft_isalnum(i));
	return(0);
}*/
