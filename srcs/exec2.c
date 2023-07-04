#include "minishell.h"

/*  char *ft_check_access gets the command name and the envp linked list, with
	each node containing all the seperated environment variable name with
	their value, except PATH that gets all of its paths terminated with '/'
	and returns the accessible path for the command */
char	*ft_check_access(char **path_tab, char *cmd_name)
{
	char	*stock;
	char	*path_accessible;
	int		i;
	
	if (!path_tab || !cmd_name)
		return (NULL);
	stock = NULL;
	path_accessible = NULL;
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
	int	built_in_child;

	if (!s || !parsed)
		return ;
	built_in_child = ft_find_built_in(s, parsed);
	if (built_in_child)
	{
		if (built_in_child == 2)
		{
			execve(parsed->command[1], &(parsed->command[1]), s->envp_char);
			parsed->path = ft_check_access(s->path_tab, parsed->command[1]);
			if (execve(parsed->path, &(parsed->command[1]), s->envp_char))
				ft_error(s, EXECVE, parsed->command[1]);
		}
		else
		{
			execve(parsed->command[0], parsed->command, s->envp_char);
			parsed->path = ft_check_access(s->path_tab, parsed->command[0]);
			if (execve(parsed->path, parsed->command, s->envp_char) < 0)
				ft_error(s, EXECVE, parsed->command[0]);
		}
	}
	exit(0);
}