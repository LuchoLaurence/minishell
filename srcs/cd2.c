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
		{
			ft_free_ptr((void *)s->old_pwd_memory);
			s->old_pwd_memory = NULL;
		}
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