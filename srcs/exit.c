#include "minishell.h"

int	ft_exit(t_struct *s, t_parsed * parsed)
{
	if (!s || !parsed)
		return (1);
	if (parsed->command[1])
		s->error = ft_atoi(parsed->command[1]) % 256;
	exit(s->error);
}