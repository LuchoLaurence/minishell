#include "minishell.h"

int	ft_find_built_in(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return (1);
	cmd = parsed->command[0];
	write(STDOUT_FILENO, "(1)\n", 4);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (ft_env(s));
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (ft_pwd());
	else if (!(parsed->next) && !(parsed->prev))
	{
		if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
			return (0);
		else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
			return (0);
	}
	write(STDOUT_FILENO, "(3)\n", 4);
	return (1);
}

void	ft_env_changing_builtin(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return ;
	cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		ft_cd(s, parsed);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_unset(s, parsed);
}
