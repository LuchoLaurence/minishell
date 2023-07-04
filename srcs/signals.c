#include "minishell.h"

void	ft_signal_handler(int signal_nb)
{
	if (signal_nb == SIGINT)
	{
		g_signal_detected = 1;	
		return ;
	}
	else if (signal_nb == SIGQUIT)
	{
		g_signal_detected = 1;	
		return ;
	}
}