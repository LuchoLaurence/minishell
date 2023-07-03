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
		if (!ft_strncmp(t->value[0], env_name))
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
	while (temp_envp && ft_strncmp(temp_envp->value[0], "PATH"))
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
	ft_node_add_back_envp(s, value, 2);
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("OLDPWD");
	value[1] = NULL;
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 1);
	value2 = malloc(sizeof(char *) * (2 + 1));
	if (!value2)
		return ;
	value2[0] = ft_strdup("SHLVL");
	value2[1] = ft_strdup("1");
	value2[2] = NULL;
	ft_node_add_back_envp(s, value2, 2);
}

/*static void	ft_copy_envp_to_export(t_struct *s)
{
	t_envp	*temp;
	char	**oldpwd;
	int		oldpwd_exists;

	if (!s)
		return ;
	temp = s->envp;
	oldpwd_exists = 0;
	oldpwd = NULL;
	while (temp)
	{
		if (!ft_strncmp(temp->value[0], "OLDPWD"))
			oldpwd_exists = 1;
		ft_node_add_back_envp_export(s, temp->value, 2);
		temp = temp->next;
	}
	if (!oldpwd_exists)
	{
		oldpwd = malloc(sizeof(char *) * 2);
		if (!oldpwd)
			return ;
		oldpwd[0] = ft_strdup("OLDPWD");
		oldpwd[1] = NULL;
		ft_node_add_back_envp_export(s, oldpwd, 1);
	}
}*/

/*	static void ft_struct_envp gets the envp and splits the lines into
	two char *str, each envp node gets its char **value */
static void	ft_struct_envp(t_struct *s, char **envp)
{
	char	**oldpwd;
	int		i;
	int		j;
	int		temp;
	int		oldpwd_exists;

	if (!s || !envp)
		return ;
	if (!(*envp))
		return (ft_create_environment(s));
	i = 0;
	j = 0;
	oldpwd_exists = 0;
	while (envp[i])
	{
		if (!ft_strncmp_length("OLDPWD=", envp[i], 7))
			oldpwd_exists = 1;
		//if (ft_strncmp("OLDPWD=", envp[i]))
		if (envp[i])
			ft_node_add_back_envp(s, ft_split_envp(envp[i], &j), 2);
		if (!ft_strncmp_length("SHLVL=", envp[i], 6))
		{
			temp = ft_atoi(ft_get_env_value(s, "SHLVL"));
			temp += 1;
			free(s->last_envp->value[1]);
			s->last_envp->value[1] = ft_strdup(ft_itoa(temp));
		}
		i++;
	}
	if (!oldpwd_exists)
	{
		oldpwd = malloc(sizeof(char *) * 2);
		if (!oldpwd)
			return ;
		oldpwd[0] = ft_strdup("OLDPWD");
		oldpwd[1] = NULL;
		ft_node_add_back_envp(s, oldpwd, 1);
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
	//ft_copy_envp_to_export(s);
	s->path_tab = ft_get_path_envp_tab(s->envp);
	s->fd_in_saved = dup(STDIN_FILENO);
	s->fd_out_saved = dup(STDOUT_FILENO);
	s->fd_err_saved = dup(STDERR_FILENO);
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
