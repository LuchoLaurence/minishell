#include "minishell.h"

void	ft_swap_ptr(t_tab_envp **tab_envp, int i, int j)
{
	t_tab_envp	*temp;

	if (!tab_envp)
		return ;
	temp = tab_envp[i];
	tab_envp[i] = tab_envp[j];
	tab_envp[j] = temp;
}

t_tab_envp	**ft_sort_tab(t_struct *s, t_tab_envp **tab_envp)
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
			result = ft_strncmp(tab_envp[i]->name, tab_envp[j]->name);
			if (result > 0)
				ft_swap_ptr(tab_envp, i, j);
			j++;
		}
		i++;
	}
	return (tab_envp);
}


t_tab_envp	**ft_fill_tab(t_struct *s, t_tab_envp **tab_envp, int nb_nodes)
{
	t_envp	*temp;
	int		i;

	if (!s || !tab_envp)
		return (NULL);
	i = 0;
	temp = s->envp;
	while (temp && i < nb_nodes)
	{
		tab_envp[i]->name = ft_strdup(temp->value[0]);
		tab_envp[i++]->nb_words = temp->nb_words;
		temp = temp->next;
	}
	return (tab_envp);
}

t_tab_envp	**ft_tab_envp(t_struct *s)
{
	t_envp		*temp;
	t_tab_envp	**tab_envp;
	int			nb_nodes;
	int			i;

	if (!s)
		return (NULL);
	temp = s->envp;
	nb_nodes = 0;
	while (temp)
	{
		nb_nodes++;
		temp = temp->next;
	}
	tab_envp = malloc(sizeof(t_tab_envp *) * (nb_nodes + 1));
	if (!tab_envp)
		return (NULL);
	i = 0;
	while (i < nb_nodes)	
	{
		tab_envp[i] = malloc(sizeof(t_tab_envp));
		if (!(tab_envp[i]))
			ft_error(s, MALLOC, "malloc");
		i++;
	}
	tab_envp[nb_nodes] = NULL;
	tab_envp = ft_fill_tab(s, tab_envp, nb_nodes);
	tab_envp = ft_sort_tab(s, tab_envp);
	return (tab_envp);
}

void	ft_print_envp_ascii_order(t_struct *s)
{
	t_tab_envp	**tab_envp;
	char		*temp;
	int			i;

	if (!s)
		return ;
	tab_envp = ft_tab_envp(s);
	i = 0;
	temp = NULL;
	while (tab_envp[i])
	{
		if (ft_strncmp("_", tab_envp[i]->name))
		{
			write(STDOUT_FILENO, "declare -x ", 11);
			write(STDOUT_FILENO, tab_envp[i]->name, ft_strlen(tab_envp[i]->name));
			if (tab_envp[i]->nb_words == 2)
			{
				write(STDOUT_FILENO, "=\"", 2);
				temp = ft_get_env_value(s, tab_envp[i]->name);
				write(STDOUT_FILENO, temp, ft_strlen(temp));
				write(STDOUT_FILENO, "\"", 1);
			}
			write(STDOUT_FILENO, "\n", 1);
		}
		i++;
	}
	i = 0;
	while (tab_envp[i] != NULL)
	{
		free(tab_envp[i]);
		i++;
	}
	free(tab_envp);
	tab_envp = NULL;
}
