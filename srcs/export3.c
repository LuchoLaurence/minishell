#include "minishell.h"

void	ft_error_export(t_struct *s, char *arg, int error)
{
	char	*str;
	char	*stock;
	char	str2[3];

	if (!arg)
		return ;
	str = NULL;
	stock = NULL;
	if (error == INVALID_OPTION)
	{
		ft_strlcpy(str2, arg, 3);
		stock = ft_strjoin("minishell: export: ", str2);
		str = ft_strjoin(stock, ": invalid option\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
		printf("ft_error_export invalid_option\n");
		s->error = 2;
	}
	else
	{
		stock = ft_strjoin("minishell: export: `", arg);
		str = ft_strjoin(stock, "\': not a valid identifier\n");
		ft_free_ptr((void *) stock);
		write(STDERR_FILENO, str, ft_strlen(str));
		ft_free_ptr((void *) str);
		printf("ft_error_export invalid_identifier\n");
		s->error = 1;
	}
}

void	ft_replace_value_export(t_struct *s, char **name_value, int i)
{
	t_envp	*temp;
	char	*stock;

	if (!s || !name_value)
		return ;
	temp = s->envp;
	while (s->envp->next)
		s->envp = s->envp->next;
	s->envp = temp;
	stock = NULL;
	while (temp)
	{
		if (!ft_strncmp(name_value[0], temp->value[0]))
			break ;
		temp = temp->next;
	}
	ft_free_ptr((void *) temp->value[1]);
	temp->value[1] = ft_strdup(name_value[1]);
	temp->nb_words = i;
}

static void	ft_change_envp_export(t_struct *s, char *str, char *result)
{
	char	**name_value;
	int		i;

	if (!s || !str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	name_value = ft_split_envp(str, &i);
	result = ft_env_exists(s->envp, name_value[0]);
	if (result)
		ft_replace_value_export(s, name_value, i);
	else
		ft_node_add_back_envp(s, name_value, i);
}

void	ft_check_args(t_struct *s, t_parsed *parsed, char *str)
{
	int	i;

	if (!s || !str)
		return ;
	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=' || (str[0] == '-' && !str[1]))
		return (ft_error_export(s, str, INVALID_IDENTIFIER));
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
		if (str[i] == '=' && !(parsed->prev && !(parsed->next)))
			return (ft_change_envp_export(s, str, NULL));
	}
	if (i < (int) ft_strlen(str))
		ft_error_export(s, str, INVALID_IDENTIFIER);
	else if (!(parsed->prev) && !(parsed->next))
		ft_change_envp_export(s, str, NULL);
}
