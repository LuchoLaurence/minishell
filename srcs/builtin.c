#include "minishell.h"

int	ft_cd(t_struct *s, t_parsed *p)
{
	char	*home_value;
	char	*new_pwd;

	if (!s || !p)
		return (1);
	home_value = ft_get_env_value(s, "HOME=");
	new_pwd = NULL;
	if (p->command)
	{
		if (p->command[1])
			chdir(p->command[1]);
		else if (home_value)
			chdir(home_value);
		new_pwd = getcwd(NULL, 0);
	}
	else
		write(2, "minishell: cd: HOME not set\n", 28);
	return (0);
}

int	ft_pwd(void)
{
	char	*current_path;
	char	*buff;

	buff = malloc(sizeof(char) * (4096 + 1));
	if (!buff)
		return (1);
	current_path = getcwd(buff, 4096);
	write(STDOUT_FILENO, current_path, ft_strlen(current_path));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}