#include "minishell.h"

/*	static int ft_error_env_pwd is called when an illegal option is written */
static int	ft_error_env_pwd(t_struct *s, char *arg)
{
	char	stock[2];
	char	*str;
	char	*str2;
	int		i;

	if (!s || !arg)
		return (127);
	i = 0;
	while (arg[i] == '-')
		i++;
	stock[0] = arg[i];
	stock[1] = '\0';
	str = ft_strjoin("env: illegal option -- ", stock);
	str2 = ft_strjoin(str, "\n");
	ft_free_ptr((void *) str);
	write(STDERR_FILENO, str2, ft_strlen(str2));
	ft_free_ptr((void *) str2);
	s->error = 1;
	return (0);
}

/*	static int ft_check_first_arg_env check the first and second arg from
	the pipeline if the command is "env" */
static int	ft_check_first_arg_env(t_struct *s, t_parsed *parsed)
{
	char	*str;
	int		i;
	int		length;

	if (!s || !parsed)
		return (0);
	str = parsed->command[1];
	length = ft_strlen(str);
	i = 0;
	s->i = 1;
	while (str && str[i] == '-')
		i++;
	if (!str || (str && i == length && i == 2 && !(parsed->command[2])))
		return (ft_env(s));
	else if (i == length || str[0] != '-')
	{
		if (i == length && !(parsed->command[2]))
			return (0);
		else
		{
			if (parsed->command[2])
				s->i = 2;
			return (2);
		}
	}
	return (ft_error_env_pwd(s, parsed->command[1]));
}

/*	int ft_find_built_in is called in the child process before execve to
	determine if the command is a built_in and if the built_in does not
	change the environment, the function will process to execute it, on
	the other side, in the parent process, the ft_env_changing_builtin
	function will not execute the built_in */
int	ft_find_built_in(t_struct *s, t_parsed *parsed)
{
	char	*cmd;
	int		error_env;

	if (!s || !parsed)
		return (1);
	error_env = 0;
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "env"))
	{
		/*if (!(parsed->command[1]))
			return (ft_env(s));
		else
			return (2);*/
		error_env = ft_check_first_arg_env(s, parsed);
		return (error_env);
	}
	else if (!ft_strncmp(cmd, "pwd"))
		return (ft_pwd(parsed));
	else if (!ft_strncmp(cmd, "echo"))
		return (ft_echo(s, parsed));
	else if (!ft_strncmp(cmd, "exit"))
		return (0);
	else if (!ft_strncmp(cmd, "export"))
	{
		if (parsed->command[1])
			return (0);
		else
		{
		printf("ENFANT\n");

			return (ft_export(s, parsed));
		}
	}
	else if (!ft_strncmp(cmd, "cd"))
		return (0);
	else if (!ft_strncmp(cmd, "unset"))
		return (0);
	return (1);
}

/*	void ft_env_changing_builtin is called in the parent process right after
	forking, it will process to execute the builtin if it changes the
	environment, on the other side, in the child process, the ft_find_built_in
	function will not execute it */
void	ft_env_changing_builtin(t_struct *s, t_parsed *parsed)
{
	char	*cmd;

	if (!s || !parsed)
		return ;
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "cd"))
		ft_cd(s, parsed);
	else if (!ft_strncmp(cmd, "exit"))
		ft_exit(s, parsed);
	else if (!ft_strncmp(cmd, "unset"))
		ft_unset(s, parsed);
	else if (parsed->command && parsed->command[1]
		&& !ft_strncmp(cmd, "export"))
	{
		printf("PARENT\n");
		ft_export(s, parsed);
	}
}

/*	int ft_last_is_builtin checks if the command from the last pipeline is
	a builtin, so that we check the error_codes and not from execve */
int	ft_last_is_builtin(t_parsed *parsed)
{
	char	*cmd;

	if (!parsed)
		return (0);
	cmd = NULL;
	if (parsed->command)
		cmd = parsed->command[0];
	if (!ft_strncmp(cmd, "cd") || !ft_strncmp(cmd, "exit")
		|| !ft_strncmp(cmd, "unset") || (parsed->command && parsed->command[1]
		&& !ft_strncmp(cmd, "export")) || !ft_strncmp(cmd, "env")
		|| !ft_strncmp(cmd, "pwd"))
			return (1);
	return (0);
}
