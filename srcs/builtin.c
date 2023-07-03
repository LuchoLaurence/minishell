#include "minishell.h"

void	ft_check_old_pwd(t_struct *s, char *old_pwd)
{
	t_envp	*temp;
	char	**value;

	if (!s)
		return ;
	temp = s->envp;
	value = NULL;
	while (temp)
	{
		if (!ft_strncmp("OLDPWD", temp->value[0]))
		{
			if (temp->value[1])
				free(temp->value[1]);
			if (s->unset_pwd > 1)
				temp->value[1] = ft_strdup(s->old_pwd_memory);
			else
			{
				temp->value[1] = old_pwd;
				temp->nb_words = 2;
			}
			if (!old_pwd && s->unset_pwd == 1)
				s->unset_pwd += 1;
			return;
		}
		temp = temp->next;
	}
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return;
	value[0] = ft_strdup("OLDPWD");
	value[1] = old_pwd;
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 2);
}

void ft_change_pwd(t_struct *s, char *new_pwd)
{
	t_envp *temp;
	char *old_pwd;

	if (!s)
		return;
	temp = s->envp;
	if (s->pwd_memory)
	{
		if (s->old_pwd_memory)
			ft_free_ptr((void *)s->old_pwd_memory);
		s->old_pwd_memory = s->pwd_memory;
	}
	s->pwd_memory = ft_strdup(new_pwd);
	old_pwd = NULL;
	while (temp)
	{
		if (!ft_strncmp("PWD", temp->value[0]))
		{
			old_pwd = temp->value[1];
			temp->value[1] = new_pwd;
			if (!(s->unset_oldpwd))
				ft_check_old_pwd(s, old_pwd);
			ft_reassign_updated_envp_char(s);
			return;
		}
		temp = temp->next;
	}
	if (s->unset_oldpwd == 0)
	{
		ft_check_old_pwd(s, old_pwd);
		ft_reassign_updated_envp_char(s);
	}
}

static int	ft_pwd_write(void)
{
	char *current_path;
	char buff[4096 + 1];

	/*buff = malloc(sizeof(char) * (4096 + 1));
	if (!buff)
		return (1);*/
	current_path = getcwd(buff, sizeof(buff));
	write(STDOUT_FILENO, current_path, ft_strlen(current_path));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

void	ft_error_cd(char *arg, int error)
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
		stock = ft_strjoin("minishell: cd: ", str2);
		str = ft_strjoin(stock, ": invalid option\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
	}
	else
	{
		stock = ft_strjoin("minishell: cd: ", arg);
		str = ft_strjoin(stock, ": No such file or directory\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
	}
}

void	ft_cd_path_home(t_struct *s, t_parsed *p, char *home_value)
{
	if (!s || !p)
		return ;
	if (p->command[1][0] == '-')
	{
		if (p->command[1][1] && p->command[1][1] == '-' && !(p->command[1][2]))
		{
			if (chdir(home_value) == -1)
				write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		}
		else if (p->command[1][1])
			ft_error_cd(p->command[1], INVALID_OPTION);
		else
		{
			if (chdir(ft_get_env_value(s, "OLDPWD")) == -1)
				write(STDERR_FILENO, "minishell: cd: OLDPWD not set HOMEMADE\n", 3);
			else
				ft_pwd_write();
		}
	}
	if (!ft_strncmp("~", p->command[1]))
	{
		if (chdir(home_value) == -1)
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
	}
	else
		chdir(p->command[1]);
}

int ft_cd(t_struct *s, t_parsed *p)
{
	char *home_value;
	char *new_pwd;
	char *buff;

	if (!s || !p)
		return (1);
	home_value = ft_get_env_value(s, "HOME");
	if (!home_value && !(p->command[1]))
		write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
	new_pwd = NULL;
	buff = malloc(sizeof(char) * (4096 + 1));
	if (!buff)
		return (1);
	if (p->command)
	{
		if (p->command[1])
			ft_cd_path_home(s, p, home_value);
		else if (home_value)
			chdir(home_value);
		new_pwd = getcwd(buff, 4096 + 1);
		ft_change_pwd(s, ft_strdup(new_pwd));
		free(buff);
	}
	/*t_envp	*temp = s->envp;
	while (temp)
	{
		printf("temp->value = %s == %s\n", temp->value[0], temp->value[1]);
		temp = temp->next;
	}*/
	return (0);
}

int ft_pwd(t_parsed *parsed)
{
	char *current_path;
	char buff[4096 + 1];

	/*buff = malloc(sizeof(char) * (4096 + 1));
	if (!buff)
		return (1);*/
	if (!parsed)
		return (0);
	if (parsed->command[1])
	{
		if (parsed->command[1][0] == '-')
		{
			if (parsed->command[1][1] != '-')
			{
				write(STDERR_FILENO, "minishell: pwd: invalid option\n", 31);
				return (0);
			}
		}
	}
	current_path = getcwd(buff, sizeof(buff));
	write(STDOUT_FILENO, current_path, ft_strlen(current_path));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}