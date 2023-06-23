#include "../srcs/minishell.h"

static int	ft_is_charset(char c)
{
	if (c == ':')
		return (1);
	if (c == '=')
		return (1);
	return (0);
}

static void	ft_translation(char const *s, int *i)
{
	int	j;

	j = 0;
	while (s[j] && ft_is_charset(s[j]))
		j++;
	*i = *i + j - 1;
}

static void	ft_translationdif(char const *s, int *i, int nb)
{
	int	j;

	j = 0;
	(void) nb;
	while (s[j] && !(ft_is_charset(s[j])))
		j++;
	*i = *i + j - 1;
}

static char	*ft_deploiementmot(char const *strpos, int *i)
{
	char	*str;
	char	*stock;
	int		j;

	j = 0;
	str = NULL;
	while (strpos[j] && !(ft_is_charset(strpos[j])))
		j++;
	stock = ft_substr(strpos, 0, j);
	*i = *i + j - 1;
	if (!ft_strncmp(stock, "PATH", 4))
		return (stock);
	str = ft_strjoin(stock, "/");
	free(stock);
	return (str);
}

/*	ft_split_add_splash splits a string of characters using a character
	called c and adds one '/' at the end of each word
	it then returns a char **stock containing all the words */
char	**ft_split_add_slash(char const *s)
{
	int			i;
	int			nb;
	char		**stock;

	if (!s)
		return (NULL);
	i = -1;
	nb = 0;
	while (s[++i])
	{
		if (ft_is_charset(s[i]))
			ft_translation(&s[i], &i);
		else if (!(ft_is_charset(s[i])))
			ft_translationdif(&s[i], &i, nb++);
	}
	stock = (char **) malloc(sizeof(char *) * (nb + 1));
	if (stock == NULL)
		return (NULL);
	i = -1;
	nb = 0;
	while (s[++i])
		if (!(ft_is_charset(s[i])))
			stock[nb++] = ft_deploiementmot(&s[i], &i);
	stock[nb] = NULL;
	return (stock);
}
