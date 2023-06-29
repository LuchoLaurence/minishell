#include "minishell.h"

int	ft_find_built_in(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return (1);
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "env") && !(parsed->next) && !(parsed->prev))
	{
		printf("entree\n");
		return (ft_env(s));
	}
	else if (!ft_strncmp(cmd, "pwd"))
		return (ft_pwd(parsed));
	else if (!ft_strncmp(cmd, "echo"))
		return (ft_echo(s, parsed));
	else if (!ft_strncmp(cmd, "exit"))
		return (0);
	else if (!ft_strncmp(cmd, "export"))
	{
		if (parsed->command[1])
			return (0);
		else
			return (ft_export(s, parsed));
	}
	else if (!ft_strncmp(cmd, "cd"))
		return (0);
	else if (!ft_strncmp(cmd, "unset"))
		return (0);
	/*else if (!(parsed->next) && !(parsed->prev))
	{
		if (!ft_strncmp(cmd, "cd"))
			return (0);
		else if (!ft_strncmp(cmd, "unset"))
			return (0);
	}*/
	return (1);
}

void	ft_env_changing_builtin(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return ;
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "cd"))
		ft_cd(s, parsed);
	else if (!ft_strncmp(cmd, "exit"))
		ft_exit(s, parsed);
	else if (!ft_strncmp(cmd, "unset"))
		ft_unset(s, parsed);
	else if (parsed->command && parsed->command[1]
		&& !ft_strncmp(cmd, "export"))
		ft_export(s, parsed);
}
