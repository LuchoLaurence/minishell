#include "minishell.h"

/*	static int ft_atoi_exit gets the verification of each char inside str
	and returns nb * sign if it is a correct number */
static int	ft_atoi_exit(const char *str, int nb)
{
	char	*s;
	int		sign;

	if (!str || (str && ft_isalpha(*str)))
		return (-2147483648);
	sign = 1;
	s = (char *) str;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -sign;
		s++;
	}
	if (*s && !ft_isdigit(*s))
		return (-2147483648);
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + (*s - 48);
		s++;
	}
	if (*s && !ft_isdigit(*s))
		return (-2147483648);
	return (nb * sign);
}

/*	static void ft_error_exit calls the correct error message and sends it
	to the STDERR_FILENO */
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

/*	int ft_exit is called when ctrl+d is pressed or when exit is written in
	non-interactive mode */
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
			s->error = ft_atoi_exit(parsed->command[1], 0);
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