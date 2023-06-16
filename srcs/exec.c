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

static void ft_pipe_and_fork(t_struct *s)
{
	if (!s || s->i_cmd >= s->nb_cmd)
		return;
	if (s->i_cmd < s->nb_cmd)
	{
		s->parsed->pipe_fd = malloc(sizeof(int) * 2);
		if (!(s->parsed->pipe_fd))
			return (ft_error(MALLOC, "malloc"));
		if (pipe(s->parsed->pipe_fd) < 0)
			return (ft_error(PIPE, "pipe"));
	}
	s->parsed->pid = fork();
	if (s->parsed->pid < 0)
		return (ft_error(FORK, "fork"));
	if (s->parsed->pid == 0)
		ft_child_process(s);
	if (s->i_cmd > 0 && s->parsed->next)
		close(s->parsed->pipe_fd[0]);
	close(s->parsed->pipe_fd[1]);
	s->i_cmd += 1;
	if (s->i_cmd == s->nb_cmd)
		ft_wait_all_processes(s);
	/*  Gerer Here_doc << */
}

void ft_exec(t_struct *s)
{
	if (!s)
		return;
	//    ft_get_commands(s);
	ft_open_files_get_fds(s);							// open all files and get fds
	while (s->i_cmd < s->nb_cmd)
		ft_pipe_and_fork(s);
}