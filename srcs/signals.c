#include "minishell.h"

void	ft_signal_handler(int signal_nb)
{
	struct termios	sa;
	struct termios	saved;

	tcgetattr(STDIN_FILENO, &sa);
	saved = sa;
	sa.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &sa);
	if (signal_nb == SIGINT)
	{
		//rl_replace_line("", STDIN_FILENO);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal_nb == SIGQUIT)
	{
		return ;
	}
}