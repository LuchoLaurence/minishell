#include "minishell.h"

static int	ft_count_pipe(char *line)
{
	int	i;
	int	count;

	if (!line)
		return (0);
	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			count += 2;
		i++;
	}
	return (count);
}

static int	ft_count_redirect(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i] == '<' && line [i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>'))
		{
			count += 2;
			i++;
		}
		else if ((line[i] == '<' && line[i + 1] != '<')
			|| (line[i] == '>' && line[i + 1] != '>'))
			count += 2;
		i++;
	}
	return (count);
}

static char	*ft_space_add(char *line, char *str, int i, int y)
{
	while (line[i])
	{
		str[y] = line [i];
		if (line[i] == '|')
		{
			str[y] = ' ';
			str[++y] = '|';
			str[++y] = ' ';
		}
		if (line[i] == '<')
		{
			if (line[i + 1] == '<')
			{
				str[y] = ' ';
				str[++y] = '<';
				str[++y] = '<';
				str[++y] = ' ';
				i++;
			}
			else
			{
				str[y] = ' ';
				str[++y] = '<';
				str[++y] = ' ';
			}
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
			{
				str[y] = ' ';
				str[++y] = '>';
				str[++y] = '>';
				str[++y] = ' ';
				i++;
			}
			else
			{
				str[y] = ' ';
				str[++y] = '>';
				str[++y] = ' ';
			}
		}
		i++;
		y++;
	}
	str[y] = '\0';
	return (str);
}

/* add a apce before and after a pipe */
static char	*ft_add_space(char *line)
{
	char	*str;
	int		count;

	count = ft_count_pipe(line);
	count += ft_count_redirect(line);
	str = malloc(sizeof(char) * (count + ft_strlen(line) + 1));
	if (!str)
		return (NULL);
	str = ft_space_add(line, str, 0 , 0);
	free(line);
	return (str);
}

void	ft_lexer(t_struct *s, char *line)
{
	char	**temp;
	int		i;

	i = -1;
	line = ft_add_space(line);
	temp = ft_minisplit(line, ' ');
	// while (temp[++i])
	// 	printf("temp de [%d] = [%s]\n", i, temp[i]);
	// i = -1;
	//temp = ft_dollar_check(s, temp, -1);
	// while (temp[++i])
	// 	printf("temp de [%d] = [%s]\n", i, temp[i]);
	//temp = ft_quote_check(temp, -1, 0, 0);
	ft_struct_token(s, temp);
	// if (!s->token)
	// 	printf("s->token = NULL\n");
	// while (s->token != NULL)
	// {
	// 	printf(" le token est : %s\n", s->token->str);
	// 	printf("le token est de type : %d\n", s->token->type);
	// 	s->token = s->token->next;
	// }
	// i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	free(line);
}

// static void	ft_node_add_back_token(t_struct *s)
// {
// 	t_token	*last;
// 	t_token	*temp;

// 	if (!s)
// 		return ;
// 	last = malloc(sizeof(t_token));
// 	if (!last)
// 		return ;
// 	last->next = NULL;
// 	last->c = '\0';
// 	last->type = cmd;
// 	if (!s->token)
// 		s->token = last;
// 	else
// 	{
// 		temp = s->token;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = last;
// 	}
// }

// static void	ft_tokenization(t_token *prov)
// {
// 	if (prov->c == '>')
// 		prov->type = redirect_out;
// 	else if (prov->c == '<')
// 		prov->type = redirect_in;
// 	else if (prov->c == '|')
// 		prov->type = pipex;
// 	else if (prov->c == '\'')
// 		prov->type = quote;
// 	else if (prov->c == '\"')
// 		prov->type = double_quote;
// 	else if (prov->c == '-')
// 		prov->type = option;
// 	else if (prov->c == '$')
// 		prov->type = v_env;
// 	else if (prov->c == ' ')
// 		prov->type = space;
// 	else
// 		prov->type = cmd;
// }

// static void	ft_lexer_order(t_struct *s)
// {
// 	char	**temp;
// 	t_token	*prov;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	prov = s->token;
// 	while (prov != NULL)
// 	{
// 		if (prov->type != 0)
// 		{
// 			i = 0;
// 			j++;

// 		}
// 		prov = prov->next;
// 	}
// }

// void	ft_lexer(t_struct *s, char *line)
// {
// 	int		i;
// 	t_token	*prov;
// 	t_token	*temp;

// 	i = 0;
// 	while (line[i])
// 	{
// 		ft_node_add_back_token(s);
// 		if (i == 0)
// 			prov = s->token;
// 		else
// 			prov = prov->next;
// 		prov->c = line[i];
// 		ft_tokenization(prov);
// 		i++;
// 	}
// 	temp = s->token;
// 	while (temp != NULL)
// 	{
// 		printf(" le token est : %c\n", temp->c);
// 		printf("le token est de type : %d\n", temp->type);
// 		temp = temp->next;
// 	}
// 	ft_lexer_order(s);
// }

// static int	ft_is_token(char c)
// {
// 	if (c == ' ' || c == '|' || c == '$')
// 		return (1);
// 	if (c == '\'' || c == '\'' || c == '-')
// 		return (1);
// 	if (c == '<' || c == '>')
// 		return (1);
// 	return (0);
// }

// void	ft_lexer(t_struct *s, char *line)
// {
// 	int		i;
// 	t_token	*prov;
// 	t_token	*temp;
// 	int		count_token;

// 	i = 0;
// 	count_token = 0;
// 	while (line[i])
// 	{
// 		if (i == 0)
// 		{
// 			ft_node_add_back_token(s);
// 			count_token++;
// 		}
// 		if (ft_is_token(line[i]) && i != 0)
// 		{
// 			ft_node_add_back_token(s);
// 			count_token++;
// 		}
// 		else

// 		if (i == 0)
// 			prov = s->token;
// 		else
// 			prov = prov->next;
// 		prov->c = line[i];
// 		ft_tokenization(prov);
// 		i++;
// 	}
// 	temp = s->token;
// 	while (temp != NULL)
// 	{
// 		printf(" le token est : %s\n", temp->str);
// 		printf("le token est de type : %d\n", temp->type);
// 		temp = temp->next;
// 	}
// }