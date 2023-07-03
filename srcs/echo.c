#include "minishell.h"

int	ft_option_n_or_not(t_struct *s, char *str)
{
	int	i;
	int	option;

	if (!s || !str)
		return (0);
	i = 2;
	option = 1;
	while (str[i] == 'n')
		i++;
	if (i != (int) ft_strlen(str))
		return (0);
	return (option);
}

int	ft_echo(t_struct *s, t_parsed *parsed)
{
	int	i;
	int	opt;

	if (!s || !parsed)
		return (1);
	i = 1;
	opt = 0;
	if (parsed->command[1] && !ft_strncmp_length(parsed->command[1], "-n", 2))
	{
		opt = ft_option_n_or_not(s, parsed->command[1]);
		if (opt == 1)
			i++;
	}
	else
		opt = 0;
	while (parsed->command[i])
	{
		write(STDOUT_FILENO, parsed->command[i],
			ft_strlen(parsed->command[i]));
		if (parsed->command[i++ + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (opt != 1)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}