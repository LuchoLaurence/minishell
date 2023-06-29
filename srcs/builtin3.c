#include "minishell.h"

void	ft_swap_ptr(char **tab_envp, int i, int j)
{
	char	*temp;

	if (!tab_envp)
		return ;
	temp = tab_envp[i];
	tab_envp[i] = tab_envp[j];
	tab_envp[j] = temp;
}

char	**ft_sort_tab(t_struct *s, char **tab_envp/*, int nb_nodes*/)
{
	int		result;
	int		i;
	int		j;

	if (!s || !tab_envp)
		return (NULL);
	i = 0;
	j = 0;
	result = 0;
	while (tab_envp[i + 1])
	{
		j = i + 1;
		while (tab_envp[j])
		{
			result = ft_strncmp(tab_envp[i], tab_envp[j], 20000000);
			if (result > 0)
				ft_swap_ptr(tab_envp, i, j);
			j++;
		}
		i++;
	}
	return (tab_envp);
}

char	**ft_fill_tab(t_struct *s, char **tab_envp, int nb_nodes)
{
	t_envp	*temp;
	int		i;

	if (!s || !tab_envp)
		return (NULL);
	i = 0;
	temp = s->envp;
	while (temp && i < nb_nodes)
	{
		tab_envp[i++] = ft_strdup(temp->value[0]);
		temp = temp->next;
	}
	return (tab_envp);
}

char	**ft_tab_envp(t_struct *s)
{
	t_envp	*temp;
	char	**tab_envp;
	int		nb_nodes;

	if (!s)
		return (NULL);
	temp = s->envp;
	nb_nodes = 0;
	while (temp)
	{
		nb_nodes++;
		temp = temp->next;
	}
	tab_envp = (char **)malloc(sizeof(char *) * (nb_nodes + 1));
	if (!tab_envp)
		return (NULL);
	tab_envp[nb_nodes] = NULL;
	tab_envp = ft_fill_tab(s, tab_envp, nb_nodes);
	tab_envp = ft_sort_tab(s, tab_envp/*, nb_nodes + 1*/);
	return (tab_envp);
}

void	ft_print_envp_ascii_order(t_struct *s)
{
	char	**tab_envp;
	char	*temp;
	int		i;

	if (!s)
		return ;
	tab_envp = ft_tab_envp(s);
	i = 0;
	temp = NULL;
	while (tab_envp[i])
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, tab_envp[i], ft_strlen(tab_envp[i]));
		write(STDOUT_FILENO, "=\"", 2);
		temp = ft_get_env_value(s, tab_envp[i]);
		write(STDOUT_FILENO, temp, ft_strlen(temp));
		write(STDOUT_FILENO, "\"\n", 2);
		i++;
	}
	ft_free_tab((void **) tab_envp);
	tab_envp = NULL;
}

/*void	ft_replace_value_envp(t_struct *s, char **name_value)
{
	t_envp	*temp;

	if (!s || !name_value)
		return ;
	temp = s->envp;
	while (temp)
	{
		if (!ft_strncmp(name_value[0], temp->value[0], ft_strlen(name_value[0])))
			break ;
		temp = temp->next;
	}
	//free(temp->value[1]);
	temp->value[1] = ft_strdup(name_value[1]);
}

int	ft_export(t_struct *s, t_parsed *parsed)
{
	char	*result;
	char	**name_value;
	int		i;

	if (!s || !parsed)
		return (1);
	i = 1;
	result = NULL;
	name_value = NULL;
	if (!(parsed->command[i]))
		ft_print_envp_ascii_order(s);
	else
	{
		while (parsed->command[i])
		{
			name_value = ft_split(parsed->command[i], '=');
			result = ft_get_env_value(s, name_value[0]);
			if (result)
			{
				ft_replace_value_envp(s, name_value);
				free(name_value);
			}
			else
				ft_node_add_back_envp(s, name_value);
			i++;
		}
		free(result);
	}
	return (0);
}*/