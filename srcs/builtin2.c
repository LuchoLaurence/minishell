#include "minishell.h"

int	ft_unset(t_struct *s, t_parsed *parsed)
{
	t_envp	*temp;
	int		i;

	if (!s || !parsed)
		return (1);
	temp = s->envp;
	i = 1;
	while (temp && parsed->command[i])
	{
		if (!ft_strncmp(temp->value[0], parsed->command[i],
			ft_strlen(parsed->command[i])))
		{
			ft_node_remove_envp(s, temp);
			i++;
			/*if (!ft_strncmp("OLDPWD", parsed->command[i],
				ft_strlen(parsed->command[i])))
			{
				s->unset_oldpwd = 1;
				s->old_pwd_memory = 
			}*/
			if (parsed->command[i])
				temp = s->envp;
			else
				break ;
		}
		else
			temp = temp->next;
	}
	return (0);
}

static void	ft_path_write(t_envp *path)
{
	int		i;
	int		j;

	if (!path)
		return ;
	i = 1;
	j = 0;
	while (path->value[i])
	{
		while (path->value[i][j] && path->value[i][j + 1])
			write(STDOUT_FILENO, &(path->value[i][j++]), 1);
		if (path->value[i + 1])
			write(STDOUT_FILENO, ":", 1);
		j = 0;
		i++;
	}
}

int	ft_env(t_struct *s)
{
	t_envp	*temp;

	if (!s)
		return (1);
	temp = s->envp;
	while (temp)
	{
		write(STDOUT_FILENO, temp->value[0], ft_strlen(temp->value[0]));
		write(STDOUT_FILENO, "=", 1);
		if (!ft_strncmp(temp->value[0], "PATH", ft_strlen(temp->value[0])))
			ft_path_write(temp);
		else
			write(STDOUT_FILENO, temp->value[1], ft_strlen(temp->value[1]));
		write(STDOUT_FILENO, "\n", 1);
		temp = temp->next;
	}
	write(STDOUT_FILENO, "HOMEMADE\n", 9);
	return (0);
}