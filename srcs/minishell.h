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
# define EXPORT 8
# define UNSET 9

# define PERMISSION_DENIED 1
# define INVALID_OPTION 2
# define INVALID_IDENTIFIER 3
# define HOME_NOT_SET 4
# define SEGFAULT 11

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>


# include <stdio.h>

/*typedef struct s_global
{
	int	signal_detected;
}	t_global;

t_global	g;*/

static sig_atomic_t g_signal_detected;


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

typedef struct s_tab_envp
{
	char	*name;
	int		nb_words;
}	t_tab_envp;

typedef struct s_envp
{
	char			**value;
	int				nb_words;
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
	struct s_redirec	*next;
	struct s_redirec	*prev;
	char				*filename;
	int					*here_d_pipe_fd;
	pid_t				pid;
	int					fd;
	t_Tokentype			type;
}	t_redirec;

typedef struct s_parsed
{
	char			**command;
	char			*path;
	pid_t			pid;
	t_redirec		*redirection;
	t_redirec		*last_redire;
	int				*here_d_pipe_fd;
	int				fd_in;
	int				fd_out;
	int				error;
	struct s_parsed	*next;
	struct s_parsed	*prev;
}	t_parsed;

typedef struct s_struct
{
	t_envp				*envp;
	t_envp				*last_envp;
	t_envp				*envp_export;
	t_token				*token;
	t_parsed			*parsed;
	char				**envp_char;
	int					*pipe_fd;
	char				**path_tab;
	char				*old_pwd_memory;
	char				*pwd_memory;
	struct sigaction	sa;
//	struct termios		termios;
//	struct termios		term_origin;
	int					unset_oldpwd;
	int					unset_pwd;
	int					previous_fd;
	int					fd_in_saved;
	int					fd_out_saved;
	int					fd_err_saved;
	int					i;
	int					j;
	int					error;
}	t_struct;

/*	Built_ins */

int		ft_cd(t_struct *s, t_parsed *p);
void	ft_check_args(t_struct *s, char *str);
int		ft_check_first_arg(t_struct *s, t_parsed *parsed);
int		ft_echo(t_struct *s, t_parsed *parsed);
int		ft_env(t_struct *s);
int		ft_exit(t_struct *s, t_parsed * parsed);
int		ft_export(t_struct *s, t_parsed *parsed);
void	ft_print_envp_ascii_order(t_struct *s);
int		ft_pwd(t_parsed *parsed);
int		ft_unset(t_struct *s, t_parsed *parsed);

/*  Errors */

void	ft_change_return_code(t_struct *s);
void	ft_close_all_previous_files_error(t_parsed *parsed);
void	ft_error(t_struct *s, int error, char *name);
void	ft_error_export(char *arg, int error);
void	ft_get_last_cmd_code(t_struct *s, t_parsed *parsed);

/*	Environment */

void	ft_reassign_updated_envp_char(t_struct *s);
void	ft_env_changing_builtin(t_struct *s, t_parsed *parsed);
char	*ft_env_exists(t_envp *envp_list, char *env_name);
void	ft_change_underscore(t_struct *s, t_parsed *parsed);
void	ft_node_remove_underscore(t_struct *s);

/*	Exec */

char	*ft_check_access(char **path_tab, char *cmd_name);
void	ft_execution(t_struct *s, t_parsed *parsed);
void	ft_exec(t_struct *s);
int		ft_find_built_in(t_struct *s, t_parsed *parsed);
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

char	**ft_envp_list_to_tab_string(t_envp	*envp);
char	*ft_get_env_value(t_struct *s, char *env_name);
char	**ft_get_path_envp_tab(t_envp *envp);
void	ft_struct_init(t_struct *s, char **envp);

/*	Signals */

void	ft_signal_handler(int signal_nb);
void	ft_signal_init(t_struct *s);

/*  Utils */

void	ft_node_add_front(t_struct *s, char *cmd_name);
void	ft_node_add_back_envp(t_struct *s, char **value, int i);
void	ft_node_add_back_parsed(t_struct *s, char **command);
void	ft_node_add_back_redirec(t_parsed *parsed, t_Tokentype type);
void	ft_node_add_back_token(t_struct *s, char *str);
void	ft_node_remove_envp(t_struct *s, t_envp *node);
char	**ft_minisplit(char *line, char c);
char	**ft_split_add_slash(char const *s);
char	**ft_split_envp(char const *s, int *i);

#endif