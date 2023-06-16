#include "minishell.h"

/*	static void ft_get_fd_last_infile gets the last redirection_in or
	double_redirection_in */
static void	ft_get_fd_last_infile(t_parsed *parsed, t_redirec *last)
{
	t_redirec	*temp_redirec;

	if (!parsed)
		return ;
	temp_redirec = last;
	while (last->next)
		last = last->next;
	while (last)
	{
		if (last->type == redirect_in || last->type == double_redirect_in)
		{
			if (last->type == redirect_in)
				parsed->fd_in = last->fd;
			else
				parsed->fd_in = last->here_d_pipe_fd[0];
			break ;
		}
		last = last->prev;
	}
}

/*	void ft_close_all_previous_files closes all the file descriptors except the
	parsed->fd_in and parsed->out, however if a double_redirection_in exists,
	it also closes the parsed->fd_in if it is setup */
void	ft_close_all_previous_files(t_parsed *parsed)
{
	t_redirec	*temp_redirec;
	int			last_redirec_in_or_double_in;

	if (!parsed)
		return ;
	temp_redirec = parsed->redirection;
	last_redirec_in_or_double_in = 0;
	ft_get_fd_last_infile(parsed, temp_redirec);
	while (temp_redirec)
	{
		if (temp_redirec->here_d_pipe_fd && temp_redirec->here_d_pipe_fd[0]
			!= parsed->fd_in)
			close(temp_redirec->here_d_pipe_fd[0]);
		if (temp_redirec->fd != -1 && (temp_redirec->fd != parsed->fd_in)
			&& (temp_redirec->fd != parsed->fd_out))
		{
			close(temp_redirec->fd);
			temp_redirec->fd = -1;
		}
		temp_redirec = temp_redirec->next;
	}
}