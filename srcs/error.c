#include "minishell.h"

/*  static void ft_functions_error takes care of the error message for pipe,
	fork or malloc failures */
static void	ft_functions_error(int error)
{
    if (error == SYNTAX)
        write(2, "syntax error\n", 13);
	else if (error == PIPE)
		write(2, "pipe failed\n", 12);
	else if (error == FORK)
		write(2, "fork failed\n", 12);
	else if (error == MALLOC)
		write(2, "malloc failed\n", 14);
}

/*  ft_error sends the right error message to the stderror (2) */
void    ft_error(t_struct *s, int error, char *name)
{
    char    *str;

    if (!name)
        return ;
	if (error == SYNTAX || error == PIPE || error == FORK || error == MALLOC)
		ft_functions_error(error);
	else if (error == EXECVE)
	{
		if (ft_strnstr(name, "/", ft_strlen(name)) || !(s->path_tab))
			str = ft_strjoin(name, ": No such file or directory\n");
		else
			str = ft_strjoin(name, ": command not found\n");
		write(2, str, ft_strlen(str));
		ft_free_ptr((void *) str);
	}
    else if (error == FIILE)
	{
		if (errno == EACCES)
			str = ft_strjoin(name, ": Permission denied\n");
		else if (errno == ENOENT)
			str = ft_strjoin(name, ": No such file or directory\n");
		write(2, str, ft_strlen(str));
		ft_free_ptr((void *) str);
	}
}