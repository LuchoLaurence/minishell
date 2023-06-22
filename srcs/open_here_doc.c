#include "minishell.h"

/*	static void ft_child_process_hd writes from the STDIN_FILENO to the
	redirection hd_pipe_fd */
static void	ft_child_process_hd(t_redirec *re)
{
	char	*line;
	char	*stock;

	if (!re)
		return ;
	close(re->here_d_pipe_fd[0]);
	stock = re->filename;
	re->filename = ft_strjoin(stock, "\n");
	free(stock);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || !(ft_strncmp(re->filename, line, ft_strlen(line))))
		{
			ft_free_ptr((void *)line);
			break;
		}
		write(re->here_d_pipe_fd[1], line, ft_strlen(line));
		ft_free_ptr((void *)line);
	}
	close(re->here_d_pipe_fd[1]);
	exit(0);
}

/*	static void ft_pipe_and_fork_hd calls a child process and wait it to end 
	and sets the parsed->here_d_pipe_fd to the newly setup redirection->
	here_d_pipe_fd */
static void	ft_pipe_and_fork_hd(t_struct *s, t_parsed *parsed, t_redirec *redi)
{
	int	error;

	if (!parsed || !redi)
		return ;
	redi->here_d_pipe_fd = malloc(sizeof(int) * 2);
	if (!(redi->here_d_pipe_fd))
		return (ft_error(s, MALLOC, "malloc"));
	if (pipe(redi->here_d_pipe_fd) < 0)
		return (ft_error(s, PIPE, "pipe"));
	redi->pid = fork();
	if (redi->pid < 0)
		return (ft_error(s, FORK, "fork"));
	if (redi->pid == 0)
		ft_child_process_hd(redi);
	close(redi->here_d_pipe_fd[1]);
	waitpid(redi->pid, &error, 0);
	if (parsed->here_d_pipe_fd && parsed->here_d_pipe_fd[0])
		close(parsed->here_d_pipe_fd[0]);
	parsed->here_d_pipe_fd = redi->here_d_pipe_fd;
}

/*	void ft_open_double_redirect_in_one_parsed opens all the
	double_redirection_in in one parsed struct */
void	ft_open_double_redirect_in_one_parsed(t_struct *s, t_parsed *parsed)
{
	t_redirec	*temp_redirec;

	if (!parsed)
		return ;
	temp_redirec = parsed->redirection;
	while (temp_redirec)
	{
		if (temp_redirec->type == double_redirect_in)
			ft_pipe_and_fork_hd(s, parsed, temp_redirec);
		if (temp_redirec->next == NULL)
			break ;
		temp_redirec = temp_redirec->next;
	}
	/*while (temp_redirec)
	{
		if (temp_redirec->type == double_redirect_in && parsed->here_d_pipe_fd
			!= temp_redirec->here_d_pipe_fd)
			close(temp_redirec->here_d_pipe_fd[0]);
		if (temp_redirec->prev == NULL)
			break;
		temp_redirec = temp_redirec->prev;
	}*/
}

/*	int ft_open_double_redirect_in opens all the double_redirection_in and
	gets the last one as the one to use per parsed struct, it then closes all
	the others on the read side [0] opened before, and it does it
	for every parsed struct */
int	ft_open_double_redirect_in(t_struct *s, t_parsed *parsed)
{
	t_parsed	*temp_parsed;

	if (!s || !parsed)
		return (1);
	temp_parsed = parsed;
	while (temp_parsed)
	{
		ft_open_double_redirect_in_one_parsed(s, temp_parsed);
		temp_parsed = temp_parsed->next;
	}
	return (0);
}
