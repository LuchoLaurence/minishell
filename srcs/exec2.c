#include "minishell.h"

/*  char *ft_check_access gets the command name and the envp linked list, with
	each node containing all the seperated environment variable name with
	their value, except PATH that gets all of its paths terminated with '/'
	and returns the accessible path for the command */
//static char	*ft_check_access(t_envp *envp, char *cmd_name)
char	*ft_check_access(char **path_tab, char *cmd_name)
{
	//char	*path_tab;
	char	*stock;
	char	*path_accessible;
	int		i;
	
	//if (!envp || !cmd_name)
	if (!path_tab || !cmd_name)
		return (NULL);
	stock = NULL;
	path_accessible = NULL;
	//path_tab = ft_get_path_envp_tab(envp);
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
	if (ft_find_built_in(s, parsed))
	{
		execve(parsed->command[0], parsed->command, s->envp_char);
		parsed->path = ft_check_access(s->path_tab, parsed->command[0]);
		if (execve(parsed->path, parsed->command, s->envp_char) < 0)
		{
			ft_error(s, EXECVE, parsed->command[0]);
			//ft_free_everything(s);
			exit(0);
		}
	}
	exit(0);
}