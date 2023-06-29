#include "minishell.h"

/*	char *ft_get_env_value returns the value for the env name value given
	or NULL if it does not find it */
/*char	*ft_get_env_value(t_struct *s, char *env_name)
{
	char	*env_value;
	t_envp	*t;

	if (!env_name)
		return (NULL);
	env_value = NULL;
	t = s->envp;
	while (t)
	{
		if (!ft_strncmp(t->value[0], env_name, ft_strlen(t->value[0])))
		{
			env_value = t->value[1];
			break ;
		}
		t = t->next;
	}
	return (env_value);
}*/

/*	char **ft_get_path_envp_tab gets the envp node that contains
	the name "PATH=" */
char	**ft_get_path_envp_tab(t_envp *envp)
{
	t_envp	*temp_envp;
	char	**path_tab;

	if (!envp)
		return (NULL);
	temp_envp = envp;
	path_tab = NULL;
	while (temp_envp && ft_strncmp(temp_envp->value[0], "PATH", 4))
		temp_envp = temp_envp->next;
	if (temp_envp && temp_envp->value && temp_envp->value[1])
		path_tab = ft_split_add_slash(temp_envp->value[1]);
	return (path_tab);
}

/*	void ft_create_environment creates a small environment if there is no
	environement at the beginning, only variables are PWD, SHLVL and _ */
void	ft_create_environment(t_struct *s)
{
	char	**value;
	char	**value2;
	char	*current_path;

	if (!s)
		return ;
	current_path = malloc(sizeof(char) * (4096 + 1));
	if (!current_path)
		return ;
	current_path = getcwd(NULL, 4096 + 1);
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("PWD");
	value[1] = ft_strdup(current_path);
	value[2] = NULL;
	free(current_path);
	ft_node_add_back_envp(s, value);
	value2 = malloc(sizeof(char *) * (2 + 1));
	if (!value2)
		return ;
	value2[0] = ft_strdup("SHLVL");
	value2[1] = ft_strdup("1");
	value2[2] = NULL;
	ft_node_add_back_envp(s, value2);
}

/*	static void ft_struct_envp gets the envp and splits the lines into
	two char *str, each envp node gets its char **value */
static void	ft_struct_envp(t_struct *s, char **envp)
{
	int		i;
	int		temp;

	if (!s || !envp)
		return ;
	if (!(*envp))
		return (ft_create_environment(s));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("OLDPWD=", envp[i], 7))
			ft_node_add_back_envp(s, ft_split(envp[i], '='));
		if (!ft_strncmp("SHLVL=", envp[i], 6))
		{
			temp = ft_atoi(ft_get_env_value(s, "SHLVL"));
			printf("temp = %d\n", temp);
			temp += 1;
			printf("temp = %d\n", temp);
			free(s->last_envp->value[1]);
			s->last_envp->value[1] = ft_strdup(ft_itoa(temp));
			printf("s->last_envp->value[0] = %s\n", s->last_envp->value[0]);
			printf("s->last_envp->value[1] = %s\n", s->last_envp->value[1]);
		}
		i++;
	}
}

/*  void ft_struct_init creates the main struct and gets the envp */
void	ft_struct_init(t_struct *s, char **envp)
{
	if (!s)
		return ;
	s->envp = NULL;
	s->token = NULL;
	s->parsed = NULL;
	ft_struct_envp(s, envp);
	s->path_tab = ft_get_path_envp_tab(s->envp);
	s->fd_in_saved = dup(STDIN_FILENO);
	s->fd_out_saved = dup(STDOUT_FILENO);
	s->pipe_fd = malloc(sizeof(int) * 2);
	if (!(s->pipe_fd))
		return (ft_error(s, MALLOC, "malloc"));
	s->old_pwd_memory = NULL;
	s->pwd_memory = NULL;
	s->unset_oldpwd = 0;
	s->unset_pwd = 0;
	s->i = 0;
	s->j = 0;
	s->error = 0;
}
