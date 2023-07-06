#include "minishell.h"

static int	ft_atoi_exit(const char *str)
{
	char	*s;
	int		nb;
	int		signe;

	if (!str || (str && ft_isalpha(*str)))
		return (-2147483648);
	nb = 0;
	signe = 1;
	s = (char *) str;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			signe = -signe;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - 48);
		s++;
	}
	return (nb * signe);
}


static void	ft_error_exit(char *arg, int error)
{
	char	*str;
	char	*stock;

	if (!arg)
		return ;
	stock = NULL;
	if (error == NUMERIC)
	{
		stock = ft_strjoin("minishell: exit: ", arg);
		str = ft_strjoin(stock, ": numeric argument required\n");
		ft_free_ptr((void *) stock);
	}
	else
		str = ft_strdup("minishell: exit: too many arguments\n");
	write(STDERR_FILENO, str, ft_strlen(str));
	ft_free_ptr((void *) str);
}

int	ft_exit(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return (1);
	if (parsed->command[1] && parsed->command[2])
	{
		s->error = 1;
		return (ft_error_exit("too many", ARGUMENTS), 0);
	}
	if (!(parsed->prev) && !(parsed->next))
	{
		if (parsed->command[1])
		{
			s->error = ft_atoi_exit(parsed->command[1]);
			if (s->error == -2147483648)
			{
				ft_error_exit(parsed->command[1], NUMERIC);
				exit(255);
			}
			else
				s->error %= 256;
		}
		write(STDOUT_FILENO, "exit\n", 5);
		exit(s->error);
	}
	return (0);
}