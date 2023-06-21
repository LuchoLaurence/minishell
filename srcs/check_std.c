#include "minishell.h"

void	ft_check_std(t_struct *s)
{
	int	check_std;

	if (!s)
		return (0);
	check_std = open("/dev/stdin", O_RDONLY);
	if (check_std == -1)
	{
		ft_error(s, STDIN, "stdin");
		exit(1);
	}
	close(check_std);
	check_std = open("/dev/stdout", O_WRONLY);
	if (check_std == -1)
	{
		ft_error(s, STDOUT, "stdin");
		exit(1);
	}
	close(check_std);
	return (1);
}