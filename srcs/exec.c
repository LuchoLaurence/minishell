#include "minishell.h"

/*static void ft_get_commands(t_struct *s)
{
	if (!s)
		return ;

}*/

static void ft_child_process(t_struct *s)
{
	if (!s)
		return;
	/* multiple here_doc possibles */						// A CODER
	if (s->parsed->next && s->parsed->next->pipe_fd)
		dup2(s->parsed->next->pipe_fd[0], STDIN_FILENO);
	else if (s->parsed->redirection_in)						// if fds
		dup2()
}

static void ft_pipe_and_fork(t_struct *s, t_parsed *parsed)
{
	if (!s || !(parsed->command))
		return ;
	if (!(parsed->prev))
	{
		s->pipe_fd = malloc(sizeof(int) * 2);
		if (!(s->pipe_fd))
			return (ft_error(MALLOC, "malloc"));
	}
	if (parsed->next)
	{
		if (pipe(s->pipe_fd) < 0)
			return (ft_error(s, PIPE, "pipe"));
	}
	s->parsed->pid = fork();
	if (s->parsed->pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (s->parsed->pid == 0)
		ft_child_process(s);
	close(s->pipe_fd[1]);
	close(s->previous_fd);
	if (parsed->next)
		dup2(s->pipe_fd[0], s->previous_fd);
	close(s->pipe_fd[0]);
	if (!(parsed->next))
		ft_wait_all_processes(s);
	if (parsed->here_d_pipe_fd)
	{
		close(parsed->pipe_fd[0]);
		fr_free_hd(parsed);
	}
	if (s->i_cmd > 0 && s->parsed->next)
		close(s->parsed->pipe_fd[0]);
	close(s->parsed->pipe_fd[1]);
}

void ft_exec(t_struct *s)
{
	t_parsed	*parsed;
	if (!s)
		return ;
	//    ft_get_commands(s);
	ft_open_files_get_fds(s);							// open all files and get fds
	parsed = s->parsed;
	while (parsed)
	{
		ft_pipe_and_fork(s, parsed);
		parsed = parsed->next;
	}
}