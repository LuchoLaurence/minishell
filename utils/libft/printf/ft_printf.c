/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan <avan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:28:38 by avan              #+#    #+#             */
/*   Updated: 2023/06/29 18:11:59 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putstrest(t_elem *e, int *nb, int l)
{
	int	temp;

	l = ft_strlen(e->s);
	temp = e->tabint[0];
	if ((e->flags & FLAG_POINT) && !(ft_strncmp(e->s, "0")) && e->spe != 's')
		ft_putelses(e, nb, l, temp);
	else if (!(e->flags & FLAG_MOINS))
	{
		while (e->tabint[0]-- > l)
			ft_putchar_printf(' ', 1, nb);
		ft_putstr_printf(e->s, 1, nb);
	}
	else
	{
		ft_putstr_printf(e->s, 1, nb);
		while (e->tabint[0]-- > l)
			ft_putchar_printf(' ', 1, nb);
	}
}

static void	ft_manags(t_elem *e, void (**f)(), va_list chain, int *nb)
{
	int	i;

	i = ft_giveindex(e->spe);
	if (e->spe == 'c')
	{
		if (e->flags & FLAG_MOINS)
		{
			ft_putchar_printf(va_arg(chain, int), 1, nb);
			while (e->tabint[0]-- > 1)
				ft_putchar_printf(' ', 1, nb);
		}
		else
		{
			while (e->tabint[0]-- > 1)
				ft_putchar_printf(' ', 1, nb);
			ft_putchar_printf(va_arg(chain, int), 1, nb);
		}
	}
	else if (e->spe == '%')
		f[i]('%', e);
	else
		f[i](va_arg(chain, void *), e);
	if (e->spe != 'c')
		ft_putstrest(e, nb, 0);
}

static int	ft_fille(const char *arg, int len, va_list chain, int *nbchar)
{
	t_elem	*e;
	void	(**f)();
	int		i;

	i = 0;
	f = malloc(sizeof(void *) * 3);
	if (f == NULL)
		return (-1);
	ft_fillf(f);
	e = NULL;
	e = ft_enew();
	e->spe = ft_givespeci(arg);
	e->elflag = ft_substr(arg, 0, len);
	i += ft_cutflag(e);
	ft_manags(e, f, chain, nbchar);
	free(f);
	f = NULL;
	free(e->elflag);
	e->elflag = NULL;
	free(e->s);
	e->s = NULL;
	free(e);
	e = NULL;
	return (i);
}

static int	ft_checkarg(const char *arg, int *i, va_list chain)
{
	int		nbchar;
	int		len;
	char	*verif;

	nbchar = 0;
	len = 0;
	if (ft_findlen(arg, &len) == -1)
		ft_putnstr_printf(&arg[1], len, &nbchar);
	else
	{
		verif = ft_substr(arg, 1, len);
		if (verif == NULL)
			return (0);
		if (!ft_isvalidflag(verif, 0, 0))
			ft_putnstr_nodouble(&arg[1], len, &nbchar);
		else
		{
			*i += ft_fille(&arg[1], len, chain, &nbchar);
			len = 2;
		}
		free(verif);
	}
	*i = *i + len;
	return (nbchar);
}

int	ft_printf(const char *arg, ...)
{
	va_list	chain;
	int		i;
	int		nbchar;

	if (!arg)
		return (-1);
	i = 0;
	nbchar = 0;
	va_start(chain, arg);
	while (arg[i])
	{
		if (arg[i] != '%')
			ft_putchar_printf(arg[i++], 1, &nbchar);
		else
			nbchar += ft_checkarg(&arg[i], &i, chain);
	}
	va_end(chain);
	return (nbchar);
}
