#include "minishell.h"

/*	void ft_get_last_cmd_code will check the access of the last command
	and gets parsed->error and s->error to 127 */
void	ft_get_last_cmd_code(t_struct *s, t_parsed *parsed)
{
	char	*temp;

	if (!s || !parsed || (parsed && !(parsed->command)))
		return ;
	temp = ft_check_access(s->path_tab, parsed->command[0]);
	if (temp == NULL)
	{
		parsed->error = 127;
		s->error = 127;
	}
	ft_free_ptr((void *) temp);	
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
//	printf("%s\n", temp_parsed->command[0]);
	waitpid(temp_parsed->pid, &error_last_cmd, 0);
//	printf("wait parent done\n");
	s->error = temp_parsed->error;
	if (error_last_cmd != 0 && s->error == 0)
		s->error = 1;
}