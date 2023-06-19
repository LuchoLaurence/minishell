#include "../srcs/minishell.h"

/*	static t_parsed *ft_create_parsed_node initialize a node of parsed */
static t_parsed	*ft_create_parsed_node(char **command)
{
	t_parsed	*parsed_node;

	//if (!command)
	//	return (NULL);
	parsed_node = malloc(sizeof(t_parsed));
	if (!parsed_node)
		return (NULL);
	parsed_node->command = command;
	parsed_node->path = NULL;
	parsed_node->redirection = NULL;
	//parsed_node->pipe_fd = NULL;
	parsed_node->here_d_pipe_fd = NULL;
	parsed_node->fd_in = 0;
	parsed_node->fd_out = 0;
	parsed_node->error = 0;
	parsed_node->next = NULL;
	parsed_node->prev = NULL;
	return (parsed_node);
}

/*	void ft_node_add_back_parsed creates a parsed node and adds it at
	the back of the parsed linked list */
void	ft_node_add_back_parsed(t_struct *s, char **command)
{
	t_parsed	*last;
	t_parsed	*temp;

	if (!s || !command)
		return ;
	last = ft_create_parsed_node(command);
	if (!(s->parsed))
		s->parsed = last;
	else
	{
		temp = s->parsed;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}

/*	void ft_node_add_back_parsed creates a envp node and adds it at
	the back of the envp linked list */
void	ft_node_add_back_envp(t_struct *s, char **value)
{
	t_envp	*last;
	t_envp	*temp;

	if (!s)
		return ;
	last = malloc(sizeof(t_envp));
	if (!last)
		return ;
	last->value = value;
	last->next = NULL;
	last->prev = NULL;
	s->last_envp = last;
	if (!s->envp)
		s->envp = last;
	else
	{
		temp = s->envp;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}

/*	void ft_node_add_back_token creates a token node and adds it at
	the back of the token linked list */
void	ft_node_add_back_token(t_struct *s, char *str)
{
	t_token	*last;
	t_token	*temp;

	if (!s || !str)
		return ;
	last = malloc(sizeof(t_token));
	if (!last)
		return ;
	last->str = str;
	last->next = NULL;
	last->prev = NULL;
	if (!(s->token))
		s->token = last;
	else
	{
		temp = s->token;
		while (temp->next)
			temp = temp->next;
		last->prev = temp;
		temp->next = last;
	}
}

/*  ft_node_add_front creates a node calling ft_node_create and adds it
	at the front of the list */
void	ft_node_add_front(t_struct *s, char *cmd_name)
{
	(void) s;
	(void) cmd_name;
	ft_node_create("ggg");
	/*t_list	*temp;

	if (!s || !cmd_name)
		return ;
	temp = ft_node_create(cmd_name);
	if (!temp)
		return ;
	if (!s->cmd)
		s->last_cmd = temp;
	if (s->cmd)
	{
		temp->next = s->cmd;
		s->cmd->prev = temp;
	}
	s->cmd = temp;*/
}
