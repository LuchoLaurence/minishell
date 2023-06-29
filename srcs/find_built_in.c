#include "minishell.h"

int	ft_find_built_in(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return (1);
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)) && !(parsed->next) && !(parsed->prev))
	{
		printf("entree\n");
		return (ft_env(s));
	}
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (ft_pwd());
	else if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ft_echo(s, parsed));
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (0);
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
	{
		if (parsed->command[1])
			return (0);
		else
			return (ft_export(s, parsed));
	}
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (0);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (0);
	/*else if (!(parsed->next) && !(parsed->prev))
	{
		if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
			return (0);
		else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
			return (0);
	}*/
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
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		ft_exit(s, parsed);
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_unset(s, parsed);
	else if (parsed->command && parsed->command[1]
		&& !ft_strncmp(cmd, "export", ft_strlen(cmd)))
		ft_export(s, parsed);
}
