#include "minishell.h"

/*	void ft_get_fd_last_infile gets the last redirection_in or
	double_redirection_in and closes the appropriate fd */
void	ft_get_fd_last_infile(t_parsed *parsed)
{
	t_redirec	*last_temp;

	if (!parsed || (parsed && !(parsed->redirection)))
		return ;
	last_temp = parsed->last_redire;
	while (last_temp)
	{
		if (last_temp->type == redirect_in)
		{
			if (parsed->here_d_pipe_fd)
			{
				close(parsed->here_d_pipe_fd[0]);
				ft_free_ptr((void *)parsed->here_d_pipe_fd);
			}
			break ;
		}
		else if (last_temp->type == double_redirect_in)
		{
			if (parsed->fd_in)
				close(parsed->fd_in);
			parsed->fd_in = last_temp->here_d_pipe_fd[0];
			break ;
		}
		last_temp = last_temp->prev;
	}
}
