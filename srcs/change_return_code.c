#include "minishell.h"

void	ft_change_return_code(t_struct *s)
{
	t_envp	*return_code;

	if (!s)
		return ;
	return_code = s->envp;
	while (return_code && ft_strncmp(return_code->value[0], "?"))
		return_code = return_code->next;
	if (return_code)
		return_code->value[1] = ft_itoa(s->error);
}