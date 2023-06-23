#include "minishell.h"

int	ft_find_built_in(t_struct *s, t_parsed *parsed)
{
	t_parsed	*p;

	if (!s || !parsed)
		return (1);
	p = parsed;
	/*if (!ft_strncmp(p->command[0], "cd", ft_strlen(p->command[0]))
		&& !(parsed->next) && !(parsed->prev))
		return (ft_cd(s, p));
	else */if (!ft_strncmp(p->command[0], "pwd", ft_strlen(p->command[0])))
		return (ft_pwd());
	return (1);
}
