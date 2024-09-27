/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miturk <miturk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:10:23 by miturk            #+#    #+#             */
/*   Updated: 2024/09/22 11:12:20 by miturk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (((s1[i] != '\0') || (s2[i] != '\0')) && i < n)
	{
		if (s1[i] != s2[i])
			return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char *s1 = "\200";
	char *s2 = "\0";
	int i1 = ((strncmp(s1, s2, 1) > 0) ? 1 :
								((strncmp(s1, s2, 1) < 0) ? -1 : 0));
	int i2 = ((ft_strncmp(s1, s2, 1) > 0) ? 1 :	
								((ft_strncmp(s1, s2, 1) < 0) ? -1 : 0));
	if (i1 == i2)
		exit(printf("TEST_SUCCESS"));
	exit(printf("TEST_FAILED"));
}*/
