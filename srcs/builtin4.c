#include "minishell.h"

int	ft_exit(t_struct *s, t_parsed * parsed)
{
	if (!s || !parsed)
		return (1);
	if (parsed->command[1])
		s->error = ft_atoi(parsed->command[1]);
	exit(s->error);
}

int	ft_echo(t_struct *s, t_parsed *parsed)
{
	int	i;

	if (!s || !parsed)
		return (1);
	i = 1;
/*	if (!(parsed->command[1]))
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	if (parsed->command[1] && parsed->command[1][0] && parsed->command[1][0] == '-')
	{
		if (parsed->command[1][1])
		{
			while (parsed->command[1])
		}
		else
			write(STDOUT_FILENO, "-", 1);
		i++;
	}*/
	if (parsed->command[1] && parsed->command[1][0] == '-' && ft_strlen(parsed->command[1]) == 1)
		write(STDOUT_FILENO, "-", 1);
	if (parsed->command[1] && !ft_strncmp(parsed->command[1], "-n", 3))
		i++;
	while (parsed->command[i])
	{
		write(STDOUT_FILENO, parsed->command[i],
			ft_strlen(parsed->command[i]));
		if (parsed->command[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (ft_strncmp(parsed->command[1], "-n", 3))
	{
		write(2, "ok\n", 3);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

void	ft_replace_value_envp(t_struct *s, char **name_value)
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
		ft_reassign_updated_envp_char(s);
	}
	return (0);
}