#include "minishell.h"

/*  void ft_free_ptr frees a simple pointer */
void ft_free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

/*	void ft_free_tab frees a pointer of pointer */
void	ft_free_tab(void **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_free_ptr((void *)tab[i]);
		i++;
	}
	free(tab);
}

/*static void ft_free_envp(t_struct *s)
{
	t_envp	*temp;

	if (!s)
		return ;
	temp = s->envp;
	while (temp)
	{
		ft_free_tab((void **)temp->value);
		ft_free_ptr((void *)temp->prev);
		s->envp = temp->next;
		ft_free_ptr((void *)temp);
		temp = s->envp;
	}
}*/

static void	ft_free_token(t_struct *s)
{
	t_token	*temp;

	if (!s)
		return ;
	temp = s->token;
	while (temp)
	{
		ft_free_ptr((void *)temp->str);
		ft_free_ptr((void *)temp->prev);
		s->token = temp->next;
		ft_free_ptr((void *)temp);
		temp = s->token;
	}
}

void ft_free_structs(t_struct *s)
{
	if (!s)
		return ;
	//ft_free_envp(s);
	if (s->token)
		ft_free_token(s);
	if (s->parsed)
		ft_free_parsed(s);
	s->i = 0;
	s->j = 0;
	//s->error = 0;
	//ft_free_ptr((void *)s->pipe_fd);
	//s->previous_fd = open("jalsjrqwbzvljafsd", O_RDONLY | O_CREAT, 0644);
}

/*  void ft_free_everything frees everything */
/*void    ft_free_everything(t_struct *s)
{
	if (!s)
		return ;
	ft_free_ptr((void *)s);
}*/