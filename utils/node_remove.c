#include "../srcs/minishell.h"

static void	ft_free_redirec_content(t_redirec *redirec)
{
	if (!redirec)
		return ;
	ft_free_ptr((void *)redirec->filename);
	if (redirec->here_d_pipe_fd)
	{
		close(redirec->here_d_pipe_fd[0]);
		ft_free_ptr((void *)redirec->here_d_pipe_fd);
	}
	else if (redirec->fd)
		close(redirec->fd);
	ft_free_ptr((void *)redirec);
}

static t_redirec	*ft_go_to_previous_fd(t_redirec *redirec)
{
	t_redirec	*previous_fd;

	if (!redirec)
		return (NULL);
	previous_fd = redirec->prev;
	while (previous_fd && previous_fd->type != redirec->type)
		previous_fd = previous_fd->prev;
	return (previous_fd);
}

void	ft_node_remove_redirec(t_parsed *parsed, t_redirec *redirec, int fd)
{
	t_redirec	*prev_re;
	t_redirec	*next_re;
	t_redirec	*temp;

	if (!parsed || !redirec)
		return ;
	temp = ft_go_to_previous_fd(redirec);
	if (temp == NULL)
		return ;
	prev_re = temp->prev;
	next_re = temp->next;
	if (prev_re)
		prev_re->next = next_re;
	if (!prev_re)
		parsed->redirection = next_re;
	if (next_re)
		next_re->prev = prev_re;
	ft_free_redirec_content(temp);
}