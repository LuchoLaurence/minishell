/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:55:00 by marvin            #+#    #+#             */
/*   Updated: 2023/06/29 18:04:50 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_compare_size(const char *s1, const char *s2)
{
	size_t			size1;
	size_t			size2;

	if (!s1 || !s2)
		return (0);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	if (size1 < size2)
		size1 = size2;
	return (size1);
}

/*	ft_strncmp compares a s1 string and a s2 string and returns
	the difference in value, 0 means it did not find any
	difference */
int	ft_strncmp(const char *s1, const char *s2)
{
	size_t			i;
	size_t			size;
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (2147483647);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	size = ft_compare_size(s1, s2);
	while (i < size)
	{
		if (str1[i] == '\0' && str2[i])
			return (str2[i] * -1);
		if (str1[i] && str2[i] == '\0')
			return (str1[i]);
		if (str1[i] == '\0' && str2[i] == '\0')
			return (0);
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
