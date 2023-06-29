/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:52:17 by marvin            #+#    #+#             */
/*   Updated: 2023/06/29 18:13:12 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_translation(char const *s, char c, int *i)
{
	int	j;

	j = 0;
	while (s[j] && s[j] == c)
		j++;
	*i = *i + j - 1;
}

static void	ft_translationdif(char const *s, char c, int *i, int nb)
{
	int	j;

	j = 0;
	(void) nb;
	while (s[j] && s[j] != c)
		j++;
	*i = *i + j - 1;
}

static char	*ft_deploiementmot(char const *strpos, char c, int *i, char **stock)
{
	int		j;
	int		nb;
	char	*str;

	j = 0;
	nb = 0;
	while (strpos[j] && strpos[j] != c)
		j++;
	str = ft_substr(strpos, 0, j);
	if (str == NULL)
	{
		while (stock[nb])
			free(stock[nb++]);
		free(stock);
		return (NULL);
	}
	*i = *i + j - 1;
	return (str);
}

/*	ft_split splits a string of char with a char and returns a char ** */
char	**ft_split(char const *s, char c)
{
	int			i;
	int			nb;
	char		**stock;

	if (!s)
		return (NULL);
	i = -1;
	nb = 0;
	while (s[++i])
	{
		if (s[i] == c)
			ft_translation(&s[i], c, &i);
		else if (s[i] != c)
			ft_translationdif(&s[i], c, &i, nb++);
	}
	stock = (char **) malloc(sizeof(char *) * (nb + 1));
	if (stock == NULL)
		return (NULL);
	i = -1;
	nb = 0;
	while (s[++i])
		if (s[i] != c)
			stock[nb++] = ft_deploiementmot(&s[i], c, &i, stock);
	stock[nb] = NULL;
	return (stock);
}
