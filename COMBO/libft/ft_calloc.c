/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:16:36 by miturk            #+#    #+#             */
/*   Updated: 2023/09/18 09:49:16 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)

{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (ptr == NULL)
			return (NULL);
	}
	else
	{
		ptr = malloc(nmemb * size);
		if (ptr == NULL)
			return (NULL);
		ft_memset(ptr, 0, nmemb * size);
	}
	return (ptr);
}
/*
int	main(void)
{
	char	*str;
    str = (char *)ft_calloc(30, 1);
    if (!str)
        write(1, "NULL", 4);
    else
        write(1, str, 30);
}*/
