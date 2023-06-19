#include "minishell.h"

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
	s->error = temp_parsed->error;
	if (error_last_cmd != 0 && s->error == 0)
		s->error = 1;
}