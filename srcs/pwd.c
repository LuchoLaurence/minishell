#include "minishell.h"

static void	ft_error_pwd(char *arg)
{
	char	*str;
	char	*stock;
	char	str2[3];

	if (!arg)
		return ;
	str = NULL;
	stock = NULL;
	ft_strlcpy(str2, arg, 3);
	stock = ft_strjoin("minishell: pwd: ", str2);
	str = ft_strjoin(stock, ": invalid option\n");
	ft_free_ptr((void *) stock);
	write(STDERR_FILENO, str, ft_strlen(str));
	ft_free_ptr((void *) str);
}

int	ft_pwd_write(void)
{
	char *current_path;
	char buff[4096 + 1];

	current_path = getcwd(buff, sizeof(buff));
	write(STDOUT_FILENO, current_path, ft_strlen(current_path));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int ft_pwd(t_parsed *parsed)
{
	char	*current_path;
	char	buff[4096 + 1];
	char	*str;
	int		i;

	if (!parsed)
		return (1);
	str = parsed->command[1];
	i = 0;
	while (str && str[i] == '-')
		i++;
	if (i >= 1)
	{
		if (!((i == 1 || i == 2) && i == (int) ft_strlen(str)))
			return (ft_error_pwd(parsed->command[1]), 0);
//		else if (i == 1 && i != (int) ft_strlen(str))
//			return (ft_error_pwd(parsed->command[1]), 0);
	}
	current_path = getcwd(buff, sizeof(buff));
	write(STDOUT_FILENO, current_path, ft_strlen(current_path));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}