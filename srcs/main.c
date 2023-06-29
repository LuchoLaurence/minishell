#include "minishell.h"

/*int	main(int argc, char **argv, char **envp)
{
	t_struct	*s;
	char		*line;

	(void) argc;
	(void) argv;
	s = malloc(sizeof(t_struct));
	if (!s)
		return (ft_error(s, MALLOC, "malloc"), 1);
	ft_struct_init(s, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || !ft_strncmp("exit\n", line))
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

int	ft_is_redirection(t_struct *s, t_parsed *parsed, char *str, int	i)
{
	if (!s || !str || (str[i] && str[i] != '<' && str[i] != '>'))
		return (0);
	if (str[i] == '<')
	{
		i++;
		if (str[i] && str[i] == '<')
		{
			ft_node_add_back_redirec(parsed, double_redirect_in);
			i++;
		}
		else
			ft_node_add_back_redirec(parsed, redirect_in);
	}
	else if (str[i] == '>')
	{
		i++;
		if (str[i] && str[i] == '>')
		{
			ft_node_add_back_redirec(parsed, double_redirect_out);
			i++;
		}
		else
			ft_node_add_back_redirec(parsed, redirect_out);
	}
	while (str[i] == ' ')
		i++;
	s->i += i;
	s->j = s->i;
	return (1);
}

int	ft_check_next_str(t_struct *s, t_parsed *parsed, char *line, t_Tokentype t)
{
	char	*stock;

	if (!s || !line)
		return (0);
	s->j = s->i;
	if (t == redirect_in || t == redirect_out || t == double_redirect_in
		|| t == double_redirect_out)
	{
		while (line[s->j] && !ft_is_redirection(s, parsed, &line[s->j], 0)
			&& line[s->j] != ' ')
			s->j += 1;
		stock = ft_substr(line, s->i, s->j);
		parsed->last_redire->filename = stock;
	}
	else
	{
		while (line[s->j] && line[s->j] != '|'
			&& line[s->j] != '<' && line[s->j] != '>' /*!ft_is_redirection(s, parsed, &line[s->j], 0) && !ft_is_special_char(s, line)*/)
			s->j += 1;
		if (s->j == s->i)
			return (0);
		stock = ft_substr(line, s->i, s->j);
		parsed->command = ft_split(stock, ' ');
		free(stock);
	}
	s->i = s->j;
	return (1);
}

/*	int ft_check_parsed_content checks if a command or a redirection is already
	in the parsed node, if not, then it is an error and returns 0 */
int	ft_check_parsed_content(t_parsed *parsed)
{
	if (!parsed)
		return (0);
	if (!parsed->command && !parsed->redirection)
		return (0);
	return (1);
}

/*	void ft_get_str takes all info until the end of the line or the next '|' */
int	ft_get_str(t_struct *s, t_parsed *parsed, char *line)
{
	if (!s || !parsed || !line)
		return (0);
	while (line[s->i] && line[s->i] == ' ')
		s->i += 1;
	if (ft_is_redirection(s, parsed, &line[s->i], 0))
	{
		if (!ft_check_next_str(s, parsed, line, parsed->last_redire->type))
			return (ft_error(s, SYNTAX, "syntax"), 0);
	}
	else if (line[s->i] == '|')
	{
		s->i += 1;
		if (!ft_check_parsed_content(parsed))
			return (ft_error(s, SYNTAX, "syntax"), 0);
		else
			return (ft_node_add_back_parsed(s, NULL), 1);
	}
	else
		ft_check_next_str(s, parsed, line, cmd);
	return (1);
}

/*	void ft_read_line interprets the prompt line and goes to the next pipe or
	end of prompt while changing the parsed node */
void	ft_read_line(t_struct *s, char *line)
{
	t_parsed	*parsed;
	
	if (!s || !line)
		return ;
	ft_node_add_back_parsed(s, NULL);
	parsed = s->parsed;
	while (line[s->i] && parsed)
	{
		if (!ft_get_str(s, parsed, line))
			break ;
		if (parsed->next)
			parsed = parsed->next;
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
		return (ft_error(s, MALLOC, "malloc"), 1);
	ft_struct_init(s, envp);
	s->envp_char = ft_envp_list_to_tab_string(s->envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || !ft_strncmp("exit\n", line))
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(line);
		ft_read_line(s, line);
		ft_exec(s);
		ft_free_structs(s);
		free(line);
		line = NULL;
	}
	close(s->fd_in_saved);
	close(s->fd_out_saved);
	//ft_free_everything(s);
	return (0);
}
