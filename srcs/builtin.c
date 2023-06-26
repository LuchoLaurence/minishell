/*#include "minishell.h"

void	ft_check_old_pwd(t_struct *s, char *old_pwd)
{
	t_envp	*temp;

	if (!s || !old_pwd)
		return ;
	temp = s->envp;
	while (temp)
	{
		if (!ft_strncmp("OLDPWD", temp->value[0], ft_strlen(temp->value[0])))
		{
			temp->value[0] = old_pwd;
			return ;
		}
		temp = temp->next;
	}
	ft_node_add_back_envp(s, &old_pwd);
}

void	ft_change_pwd(t_struct *s, char *new_pwd)
{
	t_envp	*temp;
	char	*old_pwd;

	if (!s)
		return ;
	temp = s->envp;
	while (temp)
	{
		printf("temp->value = %s\n", temp->value[0]);
		if (!ft_strncmp("PWD", temp->value[0], ft_strlen(temp->value[0])))
		{
			old_pwd = temp->value[0];
			temp->value[0] = new_pwd;
			ft_check_old_pwd(s, old_pwd);
			return ;
			//ft_node_add_back_envp(s, &old_pwd);
		}
		temp = temp->next;
	}
}

int	ft_cd(t_struct *s, t_parsed *p)
{
	char	*home_value;
	char	*new_pwd;
	char	*buff;

	if (!s || !p)
		return (1);
	home_value = ft_get_env_value(s, "HOME=");
	new_pwd = NULL;
		printf("ici\n");
	buff = malloc(sizeof(char) * (4096 + 1));
	if (!buff)
		return (1);
	if (p->command)
	{
		printf("p->command[1] = %s\n", p->command[1]);
		printf("home_value = %s\n", home_value);
		if (p->command[1])
			chdir(p->command[1]);
		else if (home_value)
			chdir(home_value);
		new_pwd = getcwd(buff, 4096 + 1);
		printf("new_pwd = %s\n", new_pwd);
		ft_change_pwd(s, ft_strdup(new_pwd));
		free(buff);
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
}*/

#include "minishell.h"

void	ft_check_old_pwd(t_struct *s, char *old_pwd)
{
	t_envp	*temp;
	char	**value;

	if (!s || !old_pwd)
		return ;
	temp = s->envp;
	value = NULL;
	while (temp)
	{
		printf("temp->name = %s === value = %s\n", temp->value[0], temp->value[1]);
		if (!ft_strncmp("OLDPWD", temp->value[0], ft_strlen(temp->value[0])))
		{
			temp->value[1] = old_pwd;
			return ;
		}
		temp = temp->next;
	}
	value = malloc(sizeof(char *) * 2);
	if (!value)
		return ;
	value[0] = ft_strdup("OLDPWD");
	value[1] = old_pwd;
	ft_node_add_back_envp(s, value);
}

void	ft_change_pwd(t_struct *s, char *new_pwd)
{
	t_envp	*temp;
	char	*old_pwd;

	if (!s)
		return ;
	temp = s->envp;
	while (temp)
	{
		if (!ft_strncmp("PWD", temp->value[0], ft_strlen(temp->value[0])))
		{
			old_pwd = temp->value[1];
			temp->value[1] = new_pwd;
			if (!(s->unset_oldpwd))
				ft_check_old_pwd(s, old_pwd);
			return ;
		}
		temp = temp->next;
	}
}

int	ft_cd(t_struct *s, t_parsed *p)
{
	char	*home_value;
	char	*new_pwd;
	char	*buff;

	if (!s || !p)
		return (1);
	home_value = ft_get_env_value(s, "HOME");
	new_pwd = NULL;
	buff = malloc(sizeof(char) * (4096 + 1));
	if (!buff)
		return (1);
	if (p->command)
	{
		if (p->command[1])
			chdir(p->command[1]);
		else if (home_value)
			chdir(home_value);
		new_pwd = getcwd(buff, 4096 + 1);
		ft_change_pwd(s, ft_strdup(new_pwd));
		free(buff);
	}
	else
		write(2, "minishell: cd: HOME not set\n", 28);
	t_envp	*temp = s->envp;
	while (temp)
	{
		printf("temp->value = %s == %s\n", temp->value[0], temp->value[1]);
		temp = temp->next;
	}
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