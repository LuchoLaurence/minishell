#include "minishell.h"

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

void	ft_signal_init(t_struct *s)
{
	if (!s)
		return ;
	//s->term_origin = s->termios;
	tcgetattr(STDIN_FILENO, &(s->termios));
	s->termios.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &(s->termios));
	s->sa.sa_handler = &ft_signal_handler;
	s->sa.sa_flags = 0;
	if (sigaction(SIGINT, &(s->sa), NULL) == -1) {
        perror("Failed to set up SIGINT handler");
    }
    else if (sigaction(SIGQUIT, &(s->sa), NULL) == -1) {
        perror("Failed to set up SIGQUIT handler");
    }
}