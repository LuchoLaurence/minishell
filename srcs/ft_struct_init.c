#include "minishell.h"

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
	ft_struct_envp(s, envp);
	s->path_tab = ft_get_path_envp_tab(s->envp);
	s->previous_fd = open("jalsjrqwbzvljafsd", O_RDONLY | O_CREAT, 0644);
	s->pipe_fd = malloc(sizeof(int) * 2);
	if (!(s->pipe_fd))
		return (ft_error(s, MALLOC, "malloc"));
	s->i_cmd = 0;
	s->i = 0;
	s->j = 0;
	s->nb_cmd = 0;
	s->nb_pipe = 0;
	s->error = 0;
}
