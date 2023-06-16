
#include "minishell.h"

/*int	main(int argc, char **argv, char **envp)
{
	t_struct	*s;
	char		*line;

	(void) argc;
	(void) argv;
	s = malloc(sizeof(t_struct));
	if (!s)
		return (ft_error(MALLOC, "malloc"), 1);
	ft_struct_init(s, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || !ft_strncmp("exit\n", line, ft_strlen(line)))
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(line);
		ft_lexer(s, line);
	}
	ft_free_everything(s);
	return (0);
}*/

void	ft_read_line(t_struct *s, char *line)
{
	if (!s || !line)
		return ;
	int	i = 0;
	int	j = 0;
	while (line[i])
	{
		if ((line[i] == '<' || line[i] == '>') && line[i + 1] == ' ')
		{
			i += 2;
			j = i;
			while (line[j] != ' ')
				j++;
			s->parsed->redirection->filename = ft_substr(line, i, j);
			if (line[i - 2] == '<')
				s->parsed->redirection->type = redirect_in;
			if (line[i - 2] == '>')
				s->parsed->redirection->type = redirect_out;
		}
		else if (!ft_strncmp(&line[i], "<<", 2) || !ft_strncmp(&line[i], ">>", 2))
		{
			i += 3;
			j = i;
			while (line[j] != ' ')
				j++;
			s->parsed->redirection->filename = ft_substr(line, i, j);
			if (!ft_strncmp(&line[i - 3], "<<", 2))
				s->parsed->redirection->type = double_redirect_in;
			else if (!ft_strncmp(&line[i - 3], ">>", 2))
				s->parsed->redirection->type = double_redirect_out;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*s;
	char		*line;

	(void) argc;
	(void) argv;
	s = malloc(sizeof(t_struct));
	if (!s)
		return (ft_error(MALLOC, "malloc"), 1);
	ft_struct_init(s, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || !ft_strncmp("exit\n", line, ft_strlen(line)))
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(line);
		ft_read_line(s, line);
		ft_open_files_get_fds(s);
	}
	//ft_free_everything(s);
	return (0);
}
