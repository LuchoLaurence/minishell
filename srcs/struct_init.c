#include "minishell.h"

/*	static void ft_create_environement2 creates the OLDPWD and ? nodes when
	there is no existing environment */
static void	ft_create_environment2(t_struct *s, char **value, char **value2)
{
	if (!s)
		return ;
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("OLDPWD");
	value[1] = NULL;
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 1);
	value2 = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value2[0] = ft_strdup("?");
	value2[1] = ft_strdup("0");
	value2[2] = NULL;
	ft_node_add_back_envp(s, value2, 0);
}

/*	void ft_create_environment creates a small environment if there is no
	environement at the beginning, only variables are PWD, SHLVL,
	? and OLDPWD */
void	ft_create_environment(t_struct *s, char **value2)
{
	char	**value;
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
	value2 = malloc(sizeof(char *) * (2 + 1));
	if (!value2)
		return ;
	value2[0] = ft_strdup("SHLVL");
	value2[1] = ft_strdup("1");
	value2[2] = NULL;
	ft_node_add_back_envp(s, value2, 2);
	ft_create_environment2(s, NULL, NULL);
}

/*	static int ft_read_and_create_envp reads the existing environment and
	creates the envp list */
static int	ft_read_and_create_envp(t_struct *s, char **envp, int oldpwd_exists)
{
	int	i;
	int	j;
	int	temp;

	if (!s || !envp)
		return (0);
	i = 0;
	j = 0;
	temp = 0;
	while (envp[i])
	{
		if (!ft_strncmp_length("OLDPWD=", envp[i], 7))
			oldpwd_exists = 1;
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
	return (oldpwd_exists);
}

/*	static void ft_struct_envp gets the envp and splits the lines into
	two char *str, each envp node gets its char **value */
static void	ft_struct_envp(t_struct *s, char **envp)
{
	char	**oldpwd;
	char	**value;
	int		oldpwd_exists;

	if (!s || !envp)
		return ;
	if (!(*envp))
		return (ft_create_environment(s, NULL));
	oldpwd_exists = ft_read_and_create_envp(s, envp, 0);
	if (!oldpwd_exists)
	{
		oldpwd = malloc(sizeof(char *) * 2);
		if (!oldpwd)
			return ;
		oldpwd[0] = ft_strdup("OLDPWD");
		oldpwd[1] = NULL;
		ft_node_add_back_envp(s, oldpwd, 1);
	}
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("?");
	value[1] = ft_strdup("0");
	value[2] = NULL;
	ft_node_add_back_envp(s, value, 0);
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
	s->envp_char = ft_envp_list_to_tab_string(s->envp);
}
