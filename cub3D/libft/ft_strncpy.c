/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:52:28 by miturk            #+#    #+#             */
/*   Updated: 2024/09/07 15:30:54 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0' && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
