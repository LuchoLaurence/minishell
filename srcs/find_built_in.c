#include "minishell.h"

int	ft_find_built_in(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return (1);
	cmd = parsed->command[0];
	if (!(parsed->next) && !(parsed->prev))
	{
		if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
			return (0);
	}
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (ft_pwd());
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (ft_env(s));
	return (1);
}
