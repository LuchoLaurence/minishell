#include "minishell.h"

/*	char *ft_get_env_value returns the value for the env name value given
	or NULL if it does not find it */
char	*ft_get_env_value(t_struct *s, char *env_name)
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
			env_value = s->envp->value[1];
			break ;
		}
		t = t->next;
	}
	return (env_value);
}

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
	if (temp_envp)
		path_tab = temp_envp->value;
	return (path_tab);
}

/*	static void ft_struct_envp gets the envp and splits the lines into
	two char *str, each envp node gets its char **value */
static void	ft_struct_envp(t_struct *s, char **envp)
{
	int		i;

	if (!s || !envp)
		return ;
	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp("PATH=", envp[i], 5)))
			ft_node_add_back_envp(s, ft_split_add_slash(envp[i]));
		else
			ft_node_add_back_envp(s, ft_split(envp[i], '='));
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
	s->i = 0;
	s->j = 0;
	s->error = 0;
}
