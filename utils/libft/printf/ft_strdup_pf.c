/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:46:43 by avan              #+#    #+#             */
/*   Updated: 2023/06/29 18:12:12 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_putmoduloinstr(t_elem *e)
{
	char	*content;

	if (!e)
		return (NULL);
	content = (char *)malloc(sizeof(char) * 2);
	content[0] = '%';
	content[1] = '\0';
	return (content);
}

int	ft_countchar(const char *s, t_elem *e)
{
	int	count;

	count = 0;
	if (e->flags & FLAG_POINT)
	{
		if (e->tabint[1] == 0)
			count = 0;
		else if (ft_strncmp(s, ""))
			count = e->tabint[1];
	}
	else
		count = ft_strlen(s);
	return (count);
}

void	ft_strdup_pf(void *adr, t_elem *e)
{
	char	*str;
	char	*content;
	int		i;
	int		count;

	if (!e)
		return ;
	if (e->spe == '%')
		content = ft_putmoduloinstr(e);
	else if (!adr && e->spe == 's')
		content = "(null)";
	else
		content = (char *) adr;
	count = ft_countchar(content, e);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return ;
	i = -1;
	while (++i < count && content[i] != '\0')
		str[i] = content[i];
	str[i] = '\0';
	e->s = str;
	if (e->spe == '%')
		free(content);
}
