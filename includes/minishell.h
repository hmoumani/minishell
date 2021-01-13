/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:53:22 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/12 17:37:37 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# define BCYN "\e[1;36m"
# define BBLU "\e[1;33m"
# define BGRN "\e[1;32m"
# define BRED "\e[1;31m"
# define RESET "\e[0m"
# define PIPE "|"
# define INPUT_RED "<"
# define OUTPUT_RED ">"
# define APP_OUTPUT_RED ">>"
# define SEMI_COLUMN ";"
# define SEP " ;|<>"

typedef	struct	s_env
{
	char		**path;
	char		*home;
	t_list		*env_head;
}				t_env;

typedef struct	s_minishell
{
	int			return_code;
	int			stat;
	char		*command_line;
	int			pos;
	int			pipe[2];
	t_list		*cmd_head;
	t_list		*cmd_tail;
	char		*read_next;
	int			forked;
	int			env_var;
	int			export;
	pid_t		last_cmd;
}				t_minishell;

typedef	struct	s_command
{
	t_list		*argv;
	t_list		*red_files;
	int			out_red;
	int			in_red;
	int			pipe[2];
}				t_command;

typedef	struct	s_red_file
{
	char		*file;
	char		type;
}				t_red_file;

t_minishell g_minishell;
t_env g_env;

int				ft_handle_cmd(char *str);
int				ft_handle_pipe(char *str);
int				ft_handle_input_red(char *str);
int				ft_handle_output_red(char *str, char *app);
int				ft_handle_semi_column(char *str);
t_command		*ft_new_command(int in, int out, int pipe);
int				ft_syntax_error(char *token);
int				ft_on_char(const char *str, int i, char *c);
int				ft_word_length(const char *s, char *c, int sp);
char			**ft_sh_split(char const *s, char *c);
void			print_commands();
void			execute_commands();
void			handle_sigint(int sig);
void			show_prompt(char *type);
void			open_redirect_files(t_command *cmd);
void			ft_free_command(void *cmd);
void			free_redirect_files();
char			*ft_quotes_convert(char *str);
t_list			*ft_array_to_lst(char **array);
char			*ft_strappend(char *str, char c);
int				get_next_word(const char *str, char *d);
char			*ft_convert_env(char *str);
char			*get_from_env(char *s);
t_list			*lstchr(t_list *head, char *s);
void			ft_echo(char **argv);
void			ft_pwd(char **argv);
int				ft_cd(char **argv);
int				ft_export(char **argv);
int				export_all(char **argv);
void			export_normal(char *string);
int				ft_unset(char **argv);
void			add_element(char *key, char *value);
void			ft_env(char **argv);
int				ft_exit(char **argv);
void			ft_free_split(char **split);
int				ft_ptr_str_len(char **ptr);
char			*get_path();
int				ft_custom_atoi(const char *str, int i, int *error);
char			*ft_get_var(char *name);
int				is_valid_identifier(char *s);
void			ft_free(void *ptr);
int				*ft_new_fd(int in, int out, int pid);
void			ft_execute(int f);
int				export_all(char **argv);
void			export_name(char *argv);
void			export_empty_string(char **argv, char **sp, int i);
void			ft_print_path(char *s);
int				ft_endwith_pipe();
int				ft_strequ(char *s1, char *s2);
void			ft_argv_convert_env(t_list **argv, t_list *prev, char *s);
int				treat_cmd(char **argv, int cmd_id);
int				is_command(char *s);
char			**ft_lst_to_array(t_list *lst);
void			ft_lstadd(t_list *lst, t_list *new);
t_list			*ft_lstremove(t_list **lst, t_list *de_l, void (*del)(void *));
void			execute_command(t_command *cmd);
void			ft_parse(void);
void			ft_check_perm(char **e_a, char **argv, struct stat sb, int ret);
void			ft_mprint(char *s1, char *s2, char *s3, char *s4);
int				ft_is_backslashed(const char *str, int i);
char			*join_path(char *s, char *s1, char *s2);

#endif
