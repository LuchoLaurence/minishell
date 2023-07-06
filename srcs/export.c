#include "minishell.h"

int	ft_check_first_arg(t_struct *s, t_parsed *parsed)
{
	char	*str;

	if (!s || !parsed)
		return (0);
	str = parsed->command[1];
	if (str[0] == '-')
	{
		if ((str[1] == '-' && !str[2]) || !str[1])
		{
			if (parsed->command[2])
				return (1);
			else if (!str[1])
				return (1);
			else
				return (ft_print_envp_ascii_order(s), 0);
		}
		else
			return (ft_error_export(s, str, INVALID_OPTION), 0); // s->error = 2
	}
	return (1);
}

int	ft_export(t_struct *s, t_parsed *parsed)
{
	char	**name_value;
	int		i;

	if (!s || !parsed)
		return (1);
	i = 1;
	name_value = NULL;
	if (!(parsed->command[i]))
		ft_print_envp_ascii_order(s);
	else
	{
		if (!ft_check_first_arg(s, parsed))
			return (0);
		while (parsed->command[i])
		{
			ft_check_args(s, parsed, parsed->command[i]); // parsed
			i++;
		}
		ft_reassign_updated_envp_char(s);
	}
	return (0);
}
