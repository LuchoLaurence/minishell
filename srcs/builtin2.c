#include "minishell.h"

void	ft_unset_oldpwd_pwd_init(t_struct *s, char *arg_name)
{
	char	*pwd;

	if (!s || !arg_name)
		return ;
	pwd = NULL;
	if (!ft_strncmp("OLDPWD", arg_name))
	{
		s->unset_oldpwd = 1;
		pwd = ft_get_env_value(s, "PWD");
		if (!pwd)
			s->old_pwd_memory = s->pwd_memory;
	}
	else if (!ft_strncmp("PWD", arg_name))
		s->unset_pwd = 1;
}

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
		if (!ft_strncmp(temp->value[0], parsed->command[i]))
		{
			ft_unset_oldpwd_pwd_init(s, parsed->command[i]);
			ft_node_remove_envp(s, temp);
			i++;
			/*if (!ft_strncmp("OLDPWD", parsed->command[i]))
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
	ft_reassign_updated_envp_char(s);
	return (0);
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
		write(STDOUT_FILENO, temp->value[1], ft_strlen(temp->value[1]));
		write(STDOUT_FILENO, "\n", 1);
		temp = temp->next;
	}
	return (0);
}