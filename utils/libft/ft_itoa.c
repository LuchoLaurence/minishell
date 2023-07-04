/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:42:48 by avan              #+#    #+#             */
/*   Updated: 2023/07/04 10:28:13 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countchar(int n, int count)
{
	if (n < 0)
		return (ft_countchar((-n), 2));
	while (n > 9)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	int		temp;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = ft_countchar(n, 1);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (NULL);
	temp = n;
	str[count] = '\0';
	if (temp < 0)
		temp *= -1;
	while (--count >= 0)
	{
		str[count] = (temp % 10) + '0';
		temp /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
