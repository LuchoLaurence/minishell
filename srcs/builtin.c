#include "minishell.h"

int	ft_cd(t_struct *s, char *path)
{
	if (!path)
		return (ft_error(s, SYNTAX, "syntax"), -1);
	if (chdir(path) == -1)
	{
		perror(path);
		return (-1);
	}
	return (0);
}

void	ft_pwd(void)
{
	char	*current_path;
	char	*buff;

	buff = malloc(sizeof(char) * (4096 + 1));
	if (!buff)
		return ;
	current_path = getcwd(buff, 4096);
	write(1, current_path, ft_strlen(current_path));
}