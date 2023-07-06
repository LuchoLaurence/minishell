#include "minishell.h"

static void	ft_error_cd(char *arg, int error)
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

static void	ft_cd_path_home(t_struct *s, t_parsed *p, char *home_value)
{
	if (!s || !p)
		return ;
	if (p->command[1][0] == '-')
	{
		if (p->command[1][1] && p->command[1][1] == '-' && !(p->command[1][2]))
		{
			if (p->command[2])
			{
				if (chdir(p->command[2]) == -1)
					ft_error_cd(p->command[2], INVALID_IDENTIFIER);
			}
			else if (chdir(home_value) == -1)
				write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
		}
		else if (p->command[1][1])
			ft_error_cd(p->command[1], INVALID_OPTION);
		else
		{
			if (chdir(ft_get_env_value(s, "OLDPWD")) == -1)
				write(STDERR_FILENO, "minishell: cd: OLDPWD not set\n", 30);
			else
				ft_pwd_write();
		}
	}
	else if (!ft_strncmp("~", p->command[1]))
	{
		if (chdir(home_value) == -1)
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
	}
	else if (chdir(p->command[1]) == -1)
		ft_error_cd(p->command[1], INVALID_IDENTIFIER);
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
		else if (!(p->prev) && !(p->next) && home_value)
			chdir(home_value);
		new_pwd = getcwd(buff, 4096 + 1);
		ft_change_pwd(s, ft_strdup(new_pwd));
	}
	free(buff);
	return (0);
}