#include "minishell.h"

/*	static void ft_close_double_redirec_parsed closes all double redirections
	in from one parsed */
static void	ft_close_double_redirec_parsed(t_parsed *parsed)
{
	t_redirec	*temp_redirec;

	if (!parsed)
		return ;
	temp_redirec = parsed->redirection;
	while (temp_redirec)
	{
		if (temp_redirec->here_d_pipe_fd && temp_redirec->here_d_pipe_fd[0]
			!= parsed->fd_in)
		{
			close(temp_redirec->here_d_pipe_fd[0]);
			ft_free_ptr((void **) &(temp_redirec->here_d_pipe_fd));
			temp_redirec->here_d_pipe_fd = NULL;
		}
		temp_redirec = temp_redirec->next;
	}
}

/*	void ft_close_all_previous_files_error calls the function
	ft_close_double_redirec_parsed, then it closes all the fds until the
	fd == -1 */
void	ft_close_all_previous_files_error(t_parsed *parsed)
{
	t_redirec	*temp_redirec;

	if (!parsed)
		return ;
	ft_close_double_redirec_parsed(parsed);
	temp_redirec = parsed->redirection;
	while (temp_redirec && temp_redirec->fd != -1)
	{
		if (temp_redirec->fd && temp_redirec->fd != parsed->fd_in &&
			temp_redirec->fd != parsed->fd_out)
		{
			close(temp_redirec->fd);
			temp_redirec->fd = 0;
		}
		temp_redirec = temp_redirec->next;
	}
}

