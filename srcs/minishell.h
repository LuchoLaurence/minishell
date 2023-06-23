#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define SYNTAX 2
# define MALLOC 3
# define PIPE 4
# define FORK 5
# define FIILE 6
# define EXECVE 7

# define PERMISSION_DENIED 1

# include <errno.h>
# include <fcntl.h>


# include <stdio.h>

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
	pid_t				pid;				// for here_doc
	int					fd;					// = -1
	t_Tokentype			type;
}	t_redirec;

typedef struct s_parsed
{
	char			**command;
	char			*path;
	pid_t			pid;
	t_redirec		*redirection;
	t_redirec		*last_redire;
//	int				*pipe_fd;
	int				*here_d_pipe_fd;
	//int				previous_fd;
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
	char		**envp_char;
	int			*pipe_fd;				// for 3 fds technique
										// check les //
	char		**path_tab;
	int			previous_fd;
	int			fd_in_saved;
	int			fd_out_saved;
	int			i;
	int			j;
	int			error;
}	t_struct;

/*	Built_ins */

int		ft_cd(t_struct *s, t_parsed *p);
int		ft_pwd(void);

/*  Errors */

void	ft_close_all_previous_files_error(t_parsed *parsed);
void	ft_error(t_struct *s, int error, char *name);
void	ft_get_last_cmd_code(t_struct *s, t_parsed *parsed);

/*	Exec */

//void	ft_close_all_previous_files(t_parsed *parsed);
char	*ft_check_access(char **path_tab, char *cmd_name);
void	ft_execution(t_struct *s, t_parsed *parsed);
void	ft_exec(t_struct *s);
int		ft_find_built_in(t_struct *s, t_parsed *parsed);
//void	ft_get_last_infile(t_parsed *parsed);
void	ft_get_fd_last_infile(t_parsed *parsed);
int		ft_open_double_redirect_in(t_struct *s, t_parsed *parsed);
int		ft_open_files_inside_pipe(t_struct *s, t_parsed *parsed);
void	ft_wait_all_processes(t_struct *s);

/*  Freeing */

//void	ft_free_everything(t_struct *s);
void	ft_free_parsed(t_struct *s);
void	ft_free_ptr(void *ptr);
void	ft_free_structs(t_struct *s);
void	ft_free_tab(void **tab);

/*  Lexer */

void	ft_lexer(t_struct *s, char *line);

/*	Init */

char	*ft_get_env_value(t_struct *s, char *env_name);
char	**ft_get_path_envp_tab(t_envp *envp);
void	ft_struct_init(t_struct *s, char **envp);

/*  Utils */

void	ft_node_add_front(t_struct *s, char *cmd_name);
void	ft_node_add_back_envp(t_struct *s, char **value);
void	ft_node_add_back_parsed(t_struct *s, char **command);
void	ft_node_add_back_redirec(t_parsed *parsed, t_Tokentype type);
void	ft_node_add_back_token(t_struct *s, char *str);
char	**ft_minisplit(char *line, char c);
char	**ft_split_add_slash(char const *s);

#endif