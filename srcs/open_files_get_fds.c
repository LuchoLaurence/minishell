#include "minishell.h"

/*	int ft_open_file_in opens the file, using redirection->filename and gets
	its file descriptor for parsed->fd_in */
int	ft_open_file_in(t_struct *s, t_parsed *parsed, t_redirec *redirection)
{
	if (!parsed || !redirection)
		return (1);
	if (redirection->filename)
	{
		redirection->fd = open(redirection->filename, O_RDONLY);
		if (redirection->fd == -1)
		{
			ft_error(s, FIILE, redirection->filename);
			parsed->error = PERMISSION_DENIED;
			return (1);
		}
	}
	if (parsed->fd_in)
		close(parsed->fd_in);
	parsed->fd_in = redirection->fd;
	return (0);
}

/*	int ft_open_file_out opens the file accordingly to the type, using
	redirection->filename and gets its file descriptor for parsed->fd_out */
int	ft_open_file_out(t_struct *s, t_parsed *parsed, t_redirec *redirection)
{
	if (!s || !parsed || !redirection)
		return (1);
	if (parsed->fd_out)
		close(parsed->fd_out);
	parsed->fd_out = open("temp2", O_WRONLY | O_CREAT, 0644);
	unlink("temp2");
	if (redirection->filename)
	{
		if (redirection->type == redirect_out)
			redirection->fd = open(redirection->filename, O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
		else
			redirection->fd = open(redirection->filename, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (redirection->fd == -1)
		{
			ft_error(s, FIILE, redirection->filename);
			parsed->error = PERMISSION_DENIED;
			exit(1);
		}
	}
	if (parsed->fd_out)
		close(parsed->fd_out);
	parsed->fd_out = redirection->fd;
	return (0);
}

/*	void ft_open_files_inside_pipe first opens all the redirections except the
	double_redirection_in, if we do not have permission to open a file, we
	immediately quit the function, so if there are still files to be opened,
	these will be not */
int	ft_open_files_inside_pipe(t_struct *s, t_parsed *parsed)
{
	t_redirec	*temp_redire;
	int			error_code;

	if (!s || !parsed || (parsed && !(parsed->redirection)))
		return (0);
	error_code = 0;
	temp_redire = parsed->redirection;
	while (temp_redire)
	{
		if (temp_redire->type == redirect_in)
			error_code = ft_open_file_in(s, parsed, temp_redire);
		else if ((temp_redire->type == redirect_out)
			|| (temp_redire->type == double_redirect_out))
			error_code = ft_open_file_out(s, parsed, temp_redire);
		if (error_code)
			return (ft_close_all_previous_files_error(parsed), 1);
		temp_redire = temp_redire->next;
	}
	ft_get_fd_last_infile(parsed);
	return (0);
}

/*	void ft_open_files_get_fds opens all double_redirection_in from every
	parsed struct first,
	then taking one parsed struct at a time, it opens all the other files
	(in, out and double_redirection_out) in the right order until we do not
	have permission.
	if every redirection_in can be opened, it stores the last one's fd_in, same
	for the redirection_out/double_redirection_out, it stores the last
	one's fd_out */
void	ft_open_files_get_fds(t_struct *s)
{
	t_parsed	*index_parsed;

	if (!s)
		return ;
	index_parsed = s->parsed;
	ft_open_double_redirect_in(s, index_parsed);
	while (index_parsed)
	{
		ft_open_files_inside_pipe(s, index_parsed);
		index_parsed = index_parsed->next;
	}
}
