/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:51:00 by marvin            #+#    #+#             */
/*   Updated: 2023/06/05 14:08:39 by avan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

/*  ft_node_create creates a node and splits the command and the options
	to fill the char **name_options and returns an initiated node */
static t_list	*ft_node_create(char *argv_cmd)
{
	(void) argv_cmd;
	/*t_list	*cmd;

	if (!argv_cmd)
		return (NULL);
	cmd = (t_list *)malloc(sizeof(t_list));
	if (!cmd)
		return (NULL);
	cmd->name_options = ft_split(argv_cmd, ' ');
	if (!(cmd->name_options))
		return (NULL);
	cmd->pipe_fd = NULL;
	cmd->path = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);*/
	return (NULL);
}

void	ft_node_add_back_envp(t_struct *s)
{
	t_envp	*last;
	t_envp	*temp;

	if (!s)
		return ;
	last = malloc(sizeof(t_envp));
	if (!last)
		return ;
	last->next = NULL;
	last->value = NULL;
	if (!s->envp)
		s->envp = last;
	else
	{
		temp = s->envp;
		while (temp->next)
			temp = temp->next;
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
