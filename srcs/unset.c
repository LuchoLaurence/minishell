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

static int	ft_check_first_arg_unset(t_struct *s, t_parsed *parsed)
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
		}
		else
			return (ft_error_unset(s, str, INVALID_OPTION), 0);
	}
	return (1);
}

static int	ft_check_args_unset(t_struct *s, char *str)
{
	int	i;

	if (!s || !str)
		return (1);
	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (ft_error_unset(s, str, INVALID_IDENTIFIER), 1);
	else if (str[0] == '-')
	{
		if (str[1] == '-' && !str[2])
			return (0);
		else
			return (ft_error_unset(s, str, INVALID_IDENTIFIER), 1);
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i < (int) ft_strlen(str))
		return (ft_error_export(s, str, INVALID_IDENTIFIER), 1);
	return (0);
}

void	ft_find_env_nodes(t_struct *s, t_parsed *parsed, int i)
{
	t_envp	*temp;

	if (!s || !parsed)
		return ;
	temp = s->envp;
	while (temp && parsed->command[i])
	{
		if (!ft_check_args_unset(s, parsed->command[i]))
		{
			while (!(parsed->prev) && !(parsed->next) && temp)
			{
				if (!ft_strncmp(temp->value[0], parsed->command[i]))
				{
					ft_unset_oldpwd_pwd_init(s, parsed->command[i]);
					ft_node_remove_envp(s, temp);
					break ;
				}
				temp = temp->next;
			}
		}
		if (parsed->command[++i])
			temp = s->envp;
		else
			break ;
	}
}

int	ft_unset(t_struct *s, t_parsed *parsed)
{
	t_envp	*temp;
	int		i;

	if (!s || !parsed)
		return (1);
	temp = s->envp;
	i = 1;
	if (parsed->command[1] && !ft_check_first_arg_unset(s, parsed))
		return (0);
	ft_find_env_nodes(s, parsed, 1);
	ft_reassign_updated_envp_char(s);
	return (0);
}
