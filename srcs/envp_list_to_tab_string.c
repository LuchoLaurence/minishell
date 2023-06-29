#include "minishell.h"

/*	static int ft_envp_nb_nodes returns the number of nodes in the envp list */
static int	ft_envp_nb_nodes(t_envp *envp)
{
	t_envp	*temp;
	int		nb_nodes;

	if (!envp)
		return (0);
	temp = envp;
	nb_nodes = 0;
	while (temp)
	{
		nb_nodes++;
		temp = temp->next;
	}
	return (nb_nodes);
}

/*	static char *ft_get_value joins the value[0] + '=' + value[1] of the
	envp node */
static char	*ft_get_value(char **value)
{
	char	*str;
	char	*stock;

	if (!value)
		return (0);
	stock = ft_strjoin(value[0], "=");
	str = ft_strjoin(stock, value[1]);
	free(stock);
	return (str);
}

/*	static char **ft_fill_tab_envp returns a char **tab filled with the value
	of the envp */
static char	**ft_fill_tab_envp(t_envp *envp, char **tab)
{
	t_envp	*temp;
	int		i;

	if (!envp || !tab)
		return (NULL);
	temp = envp;
	i = 0;
	while (temp && tab[i])
	{
		tab[i] = ft_get_value(temp->value);
		if (!(tab[i]))
			return (NULL);	//
		i++;
		temp = temp->next;
	}
	tab[i] = NULL;
	return (tab);
}

/*	char **ft_envp_list_to_tab_string gets the envp list and returns the pointer
	to a char** version of it */
char	**ft_envp_list_to_tab_string(t_envp	*envp)
{
	char	**tab;
	t_envp	*temp;

	if (!envp)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_envp_nb_nodes(envp) + 1));
	if (!tab)
		return (NULL);
	temp = envp;
	tab = ft_fill_tab_envp(envp, tab);
	return (tab);
}