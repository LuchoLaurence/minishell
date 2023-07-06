#include "minishell.h"

static void	ft_error_unset_identifier(t_struct *s, char *arg)
{
	char	*str;
	char	*stock;

	if (!s || !arg)
		return ;
	str = NULL;
	stock = NULL;
	stock = ft_strjoin("minishell: unset: `", arg);
	str = ft_strjoin(stock, "\': not a valid identifier\n");
	ft_free_ptr((void *) stock);
	write(STDERR_FILENO, str, ft_strlen(str));
	ft_free_ptr((void *) str);
	s->error = 1;
}

void	ft_error_unset(t_struct *s, char *arg, int error)
{
	char	*str;
	char	*stock;
	char	str2[3];

	if (!s || !arg)
		return ;
	str = NULL;
	stock = NULL;
	if (error == INVALID_OPTION)
	{
		ft_strlcpy(str2, arg, 3);
		stock = ft_strjoin("minishell: unset: ", str2);
		str = ft_strjoin(stock, ": invalid option\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
		s->error = 2;
	}
	else
		ft_error_unset_identifier(s, arg);
}
