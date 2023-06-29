#include "minishell.h"

/*	void ft_reassign_updated_envp_char frees the previous envp_char and
	update it */
void	ft_reassign_updated_envp_char(t_struct *s)
{
	if (!s)
		return ;
	ft_free_tab((void **) s->envp_char);
	s->envp_char = ft_envp_list_to_tab_string(s->envp);
}

static char	*ft_get_path_bin_or_last_argument(t_struct *s, char *last_argument)
{
	char	*path;
	char	*str;

	if (!s || !last_argument)
		return (NULL);
	path = ft_check_access(s->path_tab, last_argument);
	if (path)
		str = path;
	else
		str = ft_strdup(last_argument);
	return (str);
}

/*	static void ft_create_underscore_node creates the "_" node and
	adds it at the back of s->envp */
static void	ft_create_underscore_node(t_struct *s, char *last_argument)
{
	char	**value;
//	char	*path;

	if (!s || !last_argument)
		return ;
//	path = NULL;
	value = malloc(sizeof(char *) * (2 + 1));
	if (!value)
		return ;
	value[0] = ft_strdup("_");
/*	path = ft_check_access(s->path_tab, last_argument);
	if (path)
		value[1] = path;
	else
		value[1] = ft_strdup(last_argument);*/
	value[1] = ft_get_path_bin_or_last_argument(s, last_argument);
	value[2] = NULL;
	ft_node_add_back_envp(s, value);
}

/*	void ft_change_envp_node changes the node "_" or creates it if
	it does not exist and then frees the tab s->envp_char and reassigns
	it an updated one */
static void	ft_change_envp_node(t_struct *s, char *last_argument)
{
	t_envp	*temp;

	if (!s || !last_argument)
		return ;
	temp = s->envp;
	while (temp)
	{
		if (!ft_strncmp("_", temp->value[0]))
		{
			free(temp->value[1]);
			temp->value[1] = ft_get_path_bin_or_last_argument(s, last_argument);
			break ;
		}
		temp = temp->next;
	}
	if (temp == NULL)
		ft_create_underscore_node(s, last_argument);
	ft_reassign_updated_envp_char(s);
}

/*	void ft_change_underscore gets the last argument of the last command */
void	ft_change_underscore(t_struct *s, t_parsed *parsed)
{
	t_parsed	*last;
	char		*last_argument;
	int			i;

	if (!s || !parsed)
		return ;
	if (parsed->next)
		return (ft_node_remove_underscore(s));
	last = parsed;
	last_argument = NULL;
	i = 0;
	while (last->next)
		last = last->next;
	if (last->command)
	{
		while (last->command[i + 1])
			i++;
		last_argument = last->command[i];
	}
	ft_change_envp_node(s, last_argument);
}