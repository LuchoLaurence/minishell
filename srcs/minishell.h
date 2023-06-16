#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define SYNTAX 1
# define MALLOC 2
# define PIPE 3
# define FORK 4
# define FIILE 5

# define PERMISSION_DENIED 1

# include <errno.h>
# include <fcntl.h>

typedef enum e_token_type
{
	cmd,
	pipex,
	redirect_in,
	redirect_out,
	double_redirect_in,
	double_redirect_out,
	quote,	
	double_quote,	
	option,
	v_env,
	space,
}	t_Tokentype;

typedef struct s_envp
{
	char			**value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_token
{
	char			*str;
	t_Tokentype		type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redirec
{
	struct s_redirec	*next;				// = NULL
	struct s_redirec	*prev;				// = NULL
	char				*filename;			// = NULL
	int					*here_d_pipe_fd;	// = NULL
	pid_t				pid;
	int					fd;					// = -1
	t_Tokentype			type;
}	t_redirec;

typedef struct s_parsed
{
	char			**command;
	char			*path;
	pid_t			pid;
	t_redirec		*redirection;
	int				*pipe_fd;
	int				*here_d_pipe_fd;
	int				fd_in;
	int				fd_out;
	int				error;
	struct s_parsed	*next;
	struct s_parsed	*prev;
}	t_parsed;

typedef struct s_struct
{
	t_envp		*envp;
	t_envp		*last_envp;
	t_token		*token;
	t_parsed	*parsed;
	int			i_cmd;
	int			nb_cmd;
	int			nb_pipe;
	int			error;
}	t_struct;

/*  Errors */

void	ft_error(int error, char *name);

/*	Exec */

void	ft_close_all_previous_files(t_parsed *parsed);

/*  Freeing */

//void	ft_free_everything(t_struct *s);
void	ft_free_ptr(void *ptr);

/*  Lexer */

void	ft_lexer(t_struct *s, char *line);

/*	Init */

void	ft_struct_init(t_struct *s, char **envp);

/*  Utils */

void	ft_node_add_front(t_struct *s, char *cmd_name);
void	ft_node_add_back_envp(t_struct *s, char **value);
void	ft_node_add_back_parsed(t_struct *s, char **command);
void	ft_node_add_back_token(t_struct *s, char *str);
char	**ft_minisplit(char *line, char c);
char	**ft_split_add_slash(char const *s, char c);

#endif