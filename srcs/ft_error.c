#include "minishell.h"

void    ft_error(int error, char *name)
{
    char    *str;

    if (!name)
        return ;
    if (error == SYNTAX)
        write(2, "syntax error\n", 13);
    else if (error == MALLOC)
        write(2, "malloc failed\n", 14);
    else if (error == PIPE)
        write(2, "pipe error\n", 11);
    else if (error == FORK)
        write(2, "fork error\n", 11);
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