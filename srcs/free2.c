#include "minishell.h"

/*	void ft_free_redire frees all redirection nodes */
void	ft_free_redire(t_parsed *parsed)
{
	t_redirec	*temp;

	if (!parsed || (parsed && !(parsed->redirection)))
		return ;
	temp = parsed->redirection;
	while (temp)
	{
		ft_free_ptr((void *)temp->filename);
		//ft_free_ptr((void *)temp->here_d_pipe_fd);
		temp->prev = NULL;
		parsed->redirection = temp->next;
		if (temp)
			free(temp);
		temp = parsed->redirection;
	}
}

/*	void ft_free_parsed frees all parsed node */
void	ft_free_parsed(t_struct *s)
{
	t_parsed	*temp;

	if (!s || (s && !s->parsed))
		return ;
	temp = s->parsed;
	while (temp)
	{
		ft_free_tab((void **)temp->command);
		ft_free_ptr((void *)temp->path);
		ft_free_redire(temp);
		//ft_free_ptr((void *)temp->here_d_pipe_fd);
		temp->prev = NULL;
		s->parsed = temp->next;
		ft_free_ptr((void *)temp);
		temp = s->parsed;
	}
	s->parsed = NULL;
}