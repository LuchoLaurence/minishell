#include "minishell.h"

static void	ft_error_code_cd(t_struct *s, t_parsed *parsed)
{
	char	*str;
	char	*str2;
	int		i;

	if (!s || !parsed)
		return ;
	str = parsed->command[1];
	str2 = NULL;
	if (str)
		str2 = parsed->command[2];
	i = 0;
	while (str && str[i] == '-')
		i++;
	if (!((i == 1 || i == 2) && i == (int) ft_strlen(str)))
		s->error = 1;
	else if (str && (i == 1 || i == 2) && i == (int) ft_strlen(str))
	{
		if (i == 2 && str2 && chdir(str2) == -1)
			s->error = 1;
	}
	else if (str && chdir(str) == -1)
		s->error = 1;
}

/*	static void ft_error_code_env_pwd gets the error_code from the env, pwd
	pipeline if there is one, it would be executed in the child process so
	we need this function to be run in the parent process */
static void	ft_error_code_env_pwd(t_struct *s, t_parsed *parsed)
{
	char	*str;
	char	*str2;
	char	*cmd;
	int		i;

	if (!s || !parsed)
		return ;
	cmd = parsed->command[0];
	str = parsed->command[1];
	str2 = parsed->command[2];
	i = 0;
	while (str[i] == '-')
		i++;
	if (!ft_strncmp(cmd, "pwd") && !((i == 1 || i == 2) && i == (int) ft_strlen(str)))
		s->error = 1;
	else if (i > 0 && i != (int) ft_strlen(str))
		s->error = 1;
	else if (ft_strncmp(cmd, "pwd") && i == (int) ft_strlen(str)
		&& str2 && !ft_check_access(s->path_tab, str2))
		s->error = 127;
	else if (ft_strncmp(cmd, "pwd") && i == 0
		&& !ft_check_access(s->path_tab, parsed->command[1]))
		s->error = 127;
}

/*	void ft_get_last_cmd_code will check the access of the last command
	and gets parsed->error and s->error to 127 */
void	ft_get_last_cmd_code(t_struct *s, t_parsed *parsed)
{
	char	*temp;
	char	*cmd;

	if (!s || !parsed || (parsed && !(parsed->command)))
		return ;
	cmd = parsed->command[0];
	if ((!ft_strncmp(cmd, "pwd") || !ft_strncmp(cmd, "env"))
		&& parsed->command[1])
		ft_error_code_env_pwd(s, parsed);
	else if (!ft_strncmp(cmd, "cd") && parsed->command[1])
		ft_error_code_cd(s, parsed);
	else
	{
		temp = ft_check_access(s->path_tab, parsed->command[0]);
		if (temp == NULL && (ft_strncmp(cmd, "cd") && ft_strncmp(cmd, "exit")
			&& ft_strncmp(cmd, "unset") && ft_strncmp(cmd, "export")))
		{
			parsed->error = 127;
			s->error = 127;
		}
		ft_free_ptr((void *) temp);	
	}
}

/*	void ft_wait_all_processes waits for all child processes to finish and
	will check if the last command did not have problem, if options are not
	authorized but the command is accessible, s->error will be 1 */
void	ft_wait_all_processes(t_struct *s)
{
	t_parsed	*temp_parsed;
	int			error;
	int			error_last_cmd;

	if (!s)
		return ;
	temp_parsed = s->parsed;
	while (temp_parsed->next)
	{
		waitpid(temp_parsed->pid, &error, 0);
		temp_parsed = temp_parsed->next;
	}
	waitpid(temp_parsed->pid, &error_last_cmd, 0);
	if (!ft_last_is_builtin(temp_parsed))
		s->error = temp_parsed->error;
	if (error_last_cmd == SEGFAULT)
		s->error = 139;
	if (error_last_cmd != 0 && s->error == 0)
		s->error = 1;
}