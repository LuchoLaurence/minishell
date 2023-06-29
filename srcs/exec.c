#include "minishell.h"

static void	ft_child_process_stdin(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	if (s->pipe_fd)
		close(s->pipe_fd[0]);
	if (parsed->fd_in)
	{
		if (dup2(parsed->fd_in, STDIN_FILENO) == -1)
			perror("dup2 fd_in");
		close(parsed->fd_in);
	}
	else if (!(parsed->fd_in) && parsed->prev)
	{
		if (dup2(s->previous_fd, STDIN_FILENO) == -1)
			perror("dup2 previous_fd");
	}
	else
		dup2(s->fd_in_saved, STDIN_FILENO);
	close(s->previous_fd);
}

static void ft_child_process(t_struct *s, t_parsed *parsed)
{
	if (!s || !parsed)
		return ;
	parsed->error = ft_open_files_inside_pipe(s, parsed);
	if (parsed->error)
		exit(1);
	ft_child_process_stdin(s, parsed);
	if (parsed->fd_out)
	{
		if (dup2(parsed->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(parsed->fd_out);
	}
	else if (parsed->next)
	{
		if (dup2(s->pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(s->pipe_fd[1]);
	}
	else
		dup2(s->fd_out_saved, STDOUT_FILENO);
	if (!(parsed->command))
		exit(0);
	ft_execution(s, parsed);
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
		ft_free_ptr((void *)parsed->here_d_pipe_fd);
	}
	if (!(parsed->next))
		ft_wait_all_processes(s);
}

static void ft_pipe_and_fork(t_struct *s, t_parsed *parsed)
{
	if (!s)
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
	if (!(parsed->next) && !(parsed->prev))
		ft_env_changing_builtin(s, parsed);
	ft_parent_process(s, parsed);
}

void ft_exec(t_struct *s)
{
	t_parsed	*parsed;

	if (!s)
		return ;
	parsed = s->parsed;
	if (parsed->redirection)
		ft_open_double_redirect_in(s, parsed);
//	s->previous_fd = open("jalsjrqwbzvljafsd", O_RDONLY | O_CREAT, 0644);
//	unlink("jalsjrqwbzvljafsd");
	s->previous_fd = dup(STDIN_FILENO);
	ft_change_underscore(s, parsed);
	while (parsed)
	{
		ft_pipe_and_fork(s, parsed);
		parsed = parsed->next;
	}
	dup2(s->fd_in_saved, STDIN_FILENO);
	dup2(s->fd_out_saved, STDOUT_FILENO);
}