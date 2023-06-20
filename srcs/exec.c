#include "minishell.h"

static void	ft_child_process_stdin(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	close(s->pipe_fd[0]);
	if (parsed->fd_in)
	{
		dup2(parsed->fd_in, STDIN_FILENO);
		close(parsed->fd_in);
	}
	else
		dup2(s->previous_fd, STDIN_FILENO);
	close(s->previous_fd);
}

static void ft_child_process(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	//parsed->error = ft_open_files_inside_pipe(s, parsed);
	ft_child_process_stdin(s, parsed);
	if (parsed->fd_out)
	{
		dup2(parsed->fd_out, STDOUT_FILENO);
		close(parsed->fd_out);
	}
	else if (parsed->next)
		dup2(s->pipe_fd[1], STDOUT_FILENO);
	if (parsed->next)
		close(s->pipe_fd[1]);
	if (parsed->error)
		exit(1);
	ft_execution(s, parsed);
	//ft_free_everything(s, parsed);
	exit(1);
}

static void	ft_parent_process(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	if (parsed->fd_in)
		close(parsed->fd_in);
	if (parsed->fd_out)	
		close(parsed->fd_out);
	close(s->pipe_fd[1]);
	close(s->previous_fd);
	if (parsed->next)
		dup2(s->pipe_fd[0], s->previous_fd);
	close(s->pipe_fd[0]);
	if (parsed->here_d_pipe_fd)
	{
		close(parsed->here_d_pipe_fd[0]);
		fr_free_hd(parsed);
	}
	if (!(parsed->next))
		ft_wait_all_processes(s);
	//if (s->i_cmd >= 0 && s->parsed->next)
	if (parsed->next)
		close(s->pipe_fd[0]);
}

static void ft_pipe_and_fork(t_struct *s, t_parsed *parsed)
{
	if (!s || !(parsed->command))
		return ;
	if (parsed->next)
	{
		if (pipe(s->pipe_fd) < 0)
			return (ft_error(s, PIPE, "pipe"));
	}
	else
		ft_get_last_cmd_code(s, parsed);
	parsed->pid = fork();
	if (parsed->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (parsed->pid == 0)
		ft_child_process(s, parsed);
	ft_parent_process(s, parsed);
}

void ft_exec(t_struct *s)
{
	t_parsed	*parsed;
	if (!s)
		return ;
	//ft_open_files_get_fds(s);							// open all files and get fds
	parsed = s->parsed;
	//ft_open_double_redirect_in(s, parsed);
	ft_open_files_get_fds(s);
	while (parsed)
	{
		ft_pipe_and_fork(s, parsed);
		parsed = parsed->next;
	}
	unlink("jalsjrqwbzvljafsd");
}