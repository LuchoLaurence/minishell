#include "minishell.h"

/*	char **ft_get_path_envp_tab gets the envp node that contains
	the name "PATH=" */
char	**ft_get_path_envp_tab(t_envp *envp)
{
	t_envp	*temp_envp;
	char	*path_tab;

	if (!envp)
		return (NULL);
	temp_envp = envp;
	path_tab = NULL;
	while (temp_envp && !ft_strncmp(temp_envp->value[0], "PATH=", 5))
		temp_envp = temp_envp->next;
	if (temp_envp)
		path_tab = temp_envp->value;
	return (path_tab);
}

/*  ft_check_access gets the command name and the envp linked list, with
	each node containing all the seperated environment variable name with
	their value, except PATH that gets all of its paths terminated with '/'
	and returns the accessible path for the command */
static char	*ft_check_access(t_envp *envp, char *cmd_name)
{
	char	*path_tab;
	char	*stock;
	char	*path_accessible;
	int		i;
	
	if (!envp || !cmd_name)
		return (NULL);
	stock = NULL;
	path_accessible = NULL;
	path_tab = ft_get_path_envp_tab(envp);
	i = 1;
	while (path_tab[i])
	{
		stock = ft_strjoin(path_tab[i], cmd_name);
		if (!access(stock, X_OK))
		{
			path_accessible = stock;
			break ;
		}
		free(stock);
		i++;
	}
	return (path_accessible);
}

/*	void ft_execution tries to execute the absolute path, if it does not work,
	it tries all the relative paths */
void	ft_execution(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	execve(parsed->command[0], parsed->command, NULL);
	parsed->path = ft_check_access(s->envp, parsed->command[0]);
	if (execve(parsed->path, parsed->command, NULL) < 0)
	{
		ft_error(s, EXECVE, parsed->command[0]);
		//ft_free_everything(s);
		exit(0);
	}
}