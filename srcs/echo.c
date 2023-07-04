#include "minishell.h"

int	ft_option_n_or_not(t_struct *s, t_parsed *parsed, int *i)
{
	int	j;
	int	option;

	if (!s || !parsed || !i)
		return (0);
	j = 2;
	option = 0;
	while (parsed->command[*i] && !ft_strncmp_length(parsed->command[*i],
		"-n", 2))
	{
		j = 2;
		while (parsed->command[*i][j] == 'n')
			j++;
		if (j != (int) ft_strlen(parsed->command[*i]))
			return (option);
		else
			option = 1;
		*i += 1;
	}
	return (option);
}

int	ft_echo(t_struct *s, t_parsed *parsed)
{
	int	i;
	int	opt;

	if (!s || !parsed)
		return (1);
	i = 1;
	opt = ft_option_n_or_not(s, parsed, &i);
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