/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:53:22 by ojoubout          #+#    #+#             */
/*   Updated: 2020/12/13 12:53:28 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include "../ft_printf/ft_printf.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>


#define BCYN "\e[1;36m"
#define BBLU "\e[1;33m"
#define BGRN "\e[1;32m"
#define BRED "\e[1;31m"
#define RESET "\e[0m"
// #define CMD NULL
#define PIPE "|"
#define INPUT_RED "<"
#define OUTPUT_RED ">" 
#define APP_OUTPUT_RED ">>"
#define SEMI_COLUMN ";"
#define SEP " ;|<>"

typedef struct s_env{
	char **path;
	char *home;
	t_list *env_head;
}               t_env;

typedef struct  s_minishell
{ 
	int         return_code;
	int         stat;
	char        *command_line;
	int         pos;
	int         pipe[2];
	t_list      *cmd_head;
	t_list      *cmd_tail;
	char        *read_next;
	int         forked;
}               t_minishell;

typedef struct  s_command
{
	t_list  *argv;
	// char    **argv;
	t_list  *outFiles;
	t_list  *aoutFiles;
	t_list  *inFiles;
	int     outRed;
	int     inRed;
	// char    *read_next;
}               t_command;

// typedef struct  s_cmd_list
// {
//     t_command   cmd;
//     t_cmd_list   *next;
// }               t_cmd_list;


t_minishell g_minishell;
t_env g_env;

int         ft_handle_cmd(char *str);
int         ft_handle_pipe(char *str);
int         ft_handle_input_red(char *str);
int         ft_handle_output_red(char *str, char *app);
int         ft_handle_semi_column(char *str);

void        ft_error(char *str);
t_command   *ft_new_command(int in, int out);
int         ft_syntax_error(char *token);

int	ft_on_char(const char *str, int i, char *c);
int	ft_word_length(const char *s, char *c);
char		**ft_sh_split(char const *s, char *c);
void    print_commands();
void    execute_commands();
void    handle_sigint(int sig);
void    show_prompt();
void    open_redirect_files(t_command *cmd);
void    ft_free_command(void *cmd);
void    free_redirect_files();
t_list	*ft_array_to_lst(char **array);
t_list *lstchr(t_list *head, char *s);
char *get_home();
void ft_echo(char **argv);
void ft_pwd(char **argv);
void ft_cd(char **argv);
void    ft_export(char **argv);
void ft_unset(char **argv);
void ft_env(char **argv);



// char	**ft_free(char **ptr, size_t size);

#endif