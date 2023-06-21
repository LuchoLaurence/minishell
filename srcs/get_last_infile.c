#include "minishell.h"

/*	void ft_get_fd_last_infile gets the last redirection_in or
	double_redirection_in and closes the appropriate fd */
void	ft_get_fd_last_infile(t_parsed *parsed)
{
	t_redirec	*last_temp;

	if (!parsed)
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

/*	void ft_close_all_previous_files closes all the file descriptors except the
	parsed->fd_in and parsed->fd_out, however if a double_redirection_in
	exists, it also closes the parsed->fd_in if it is setup */
/*static void	*ft_close_all_previous_files(t_parsed *parsed)
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
			ft_free_ptr(temp_redirec->here_d_pipe_fd);
			temp_redirec->here_d_pipe_fd = NULL;
		}
		else if (temp_redirec->fd && (temp_redirec->fd != parsed->fd_in)
			&& (temp_redirec->fd != parsed->fd_out))
		{
			close(temp_redirec->fd);
			temp_redirec->fd = 0;
		}
		temp_redirec = temp_redirec->next;
	}
}*/

/*	void ft_get_last_infile calls the function ft_get_fd_last_infile then
	closes all the previous file descriptors that are not the last fd_in or
	fd_out */
/*void	ft_get_last_infile(t_parsed *parsed)
{
	t_redirec	*temp_redirec;
	t_redirec	*last;

	if (!parsed || (parsed && !parsed->redirection))
		return ;
	temp_redirec = parsed->redirection;
	last = parsed->redirection;
	while (last->next)
		last = last->next;
	ft_get_fd_last_infile(parsed, last);*/
	//ft_close_all_previous_files(parsed);
	/*if (last_redirec_in && last_redirec_in->type == redirect_in)
	{
		parsed->previous_fd = open("jalsjrqwbzvljafsd", O_RDONLY | O_CREAT, 0644);
		dup2(last_redirec_in->fd, parsed->previous_fd);
		close(last_redirec_in->fd);
	}*/
//}