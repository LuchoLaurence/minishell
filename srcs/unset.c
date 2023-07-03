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

/*void	ft_unset_envp_export(t_struct *s, t_parsed *parsed)
{
	t_envp	*temp;
	int		i;

	if (!s || !parsed)
		return ;
	temp = s->envp_export;
	i = 1;
	while (temp && parsed->command[i])
	{
		if (!ft_strncmp(temp->value[0], parsed->command[i]))
		{
			ft_node_remove_envp_export(s, temp);
			i++;
			if (parsed->command[i])
				temp = s->envp_export;
			else
				break ;
		}
		else
			temp = temp->next;
		if (!temp && parsed->command[i++])
			temp = s->envp_export;
	}
}*/

static void	ft_error_unset(char	*arg, int error)
{
	char	*str;
	char	*stock;
	char	str2[3];

	if (!arg)
		return ;
	str = NULL;
	stock = NULL;
	if (error == INVALID_OPTION)
	{
		ft_strlcpy(str2, arg, 3);
		stock = ft_strjoin("minishell: unset: ", str2);
		str = ft_strjoin(stock, ": invalid option\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
	}
	else
	{
		stock = ft_strjoin("minishell: unset: `", arg);
		str = ft_strjoin(stock, "\': not a valid identifier\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
	}
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
			/*else
				return (ft_print_envp_ascii_order(s), 0);*/
		}
		else
			return (ft_error_unset(str, INVALID_OPTION), 0); // s->error = 2
	}
	return (1);
}

/*static int	ft_check_args_unset(t_struct *s, char *str)
{
	int	i;

	if (!s || !str)
		return (0);
	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=' || (str[0] == '-' && !str[1]))
		return (ft_error_export(str, INVALID_IDENTIFIER), 0); // s->error = 1
	while (str[i])
	{
		if (!ft_isaslnum(str[i]))
	}
	return (1);
}*/

static int	ft_check_args_unset(t_struct *s, char *str)
{
	int	i;

	if (!s || !str)
		return (1);
	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (ft_error_unset(str, INVALID_IDENTIFIER), 1);
	else if (str[0] == '-')
	{
		if (str[1] == '-' && !str[2])
			return (0);
		else
			return (ft_error_unset(str, INVALID_IDENTIFIER), 1); // s->error = 2
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i < (int) ft_strlen(str))
		return (ft_error_export(str, INVALID_IDENTIFIER), 1);
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
			while (temp)
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
	//if (parsed->command[1] && ft_check_invalid_identifier(s, parsed))
	//	return (ft_error(s, UNSET, parsed->command[1]));
	if (parsed->command[1] && !ft_check_first_arg_unset(s, parsed))
		return (0);
	ft_find_env_nodes(s, parsed, 1);
	/*while (temp && parsed->command[i])
	{
		if (!ft_check_args_unset(s, parsed->command[i]))
		{
			while (temp)
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
	}*/
	ft_reassign_updated_envp_char(s);
	return (0);


		/*if (!ft_strncmp(temp->value[0], parsed->command[i]))
		{
			ft_unset_oldpwd_pwd_init(s, parsed->command[i]);
			ft_node_remove_envp(s, temp);
			i++;
			if (!ft_strncmp("OLDPWD", parsed->command[i]))
			{
				s->unset_oldpwd = 1;
				s->old_pwd_memory =  
			}
			if (parsed->command[i])
				temp = s->envp;
			else
				break ;
		}
		else
			temp = temp->next;
		if (!temp && parsed->command[i++])
			temp = s->envp;
	}
	//ft_unset_envp_export(s, parsed);*/
}
