/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:42:16 by mnaumann          #+#    #+#             */
/*   Updated: 2024/12/04 20:14:50 by bszikora         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
#define MINISHELL_H

#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include "libft/libft.h"

#define MAX_ARGS 64
#define MAX_PATH 1024

typedef struct s_command t_command;

typedef enum e_token_syntax_state {
    SYNTAX_VALID = 0,
    SYNTAX_INCOMPLETE = 1,
    SYNTAX_ERROR = 2
} t_token_syntax_state;

typedef enum e_token_role 
{
    ROLE_DELIMITER = 0, //QUOTES!!!
    ROLE_BUILTIN = 1,   //This not!
    ROLE_EXECUTABLE = 2, //THIS!!!
    ROLE_ARGUMENT = 3, //DEFAULT AFTER EXECUTABLE!
    ROLE_VARIABLE = 4, //ENV VAR (don#t expand yet, function is there)
    ROLE_REDIRECT = 5, //>, <, >>, <<
    ROLE_PIPE = 6,
    ROLE_ERROR = -1, // for command not found -> at another point or call function already there
    ROLE_DEFAULT = -2 //maybe not needed, default to 3, first token defaults to 2
} t_token_role;

typedef enum e_builtin 
{
    echo = 0,
    cd = 1,
    pwd = 2,
    export = 3,
    unset = 4,
    env = 5,
    exit_cmd = 6
} t_builtin;

typedef enum e_redir_type 
{
    REDIR_NONE = 0,
    REDIR_IN = 1,
    REDIR_OUT = 2,
    REDIR_APPEND = 3,
    REDIR_HEREDOC = 4
} t_redir_type;

typedef struct s_token {
    char *content;
    int role; //0 = nothing special, 1 = command, 2 = executable, 3 = argument, 4 = string/variable to expand/read, -1 = error (not found)
    int quote_state;
    int position;
    int command_expected;
    int syntax_state;
    struct s_token *next;
    struct s_token *prev;
} t_token;

typedef enum e_quote_state {
    NO_QUOTE = 0,
    WITHIN_SINGLE_QUOTE = 1,
    WITHIN_DOUBLE_QUOTE = 2,
    UNCLOSED_SINGLE_QUOTE = 3,
    UNCLOSED_DOUBLE_QUOTE = 4
} t_quote_state;

typedef struct s_env_var {
    char *string;
    char *key;
    char *value;
    int length;
    int format; //depending on if called via export, echo or env, 0 = export, 1 = env, 2 = echo, 3= echo -n
    struct s_env_var *next;
    struct s_env_var *prev;
} t_env_var;

typedef struct s_raw_token {
    char *segment;            // Original input segment
    int quote_state;          // From e_quote_state enum
    int position;             // Start position in original input
    struct s_raw_token *next;
    struct s_raw_token *prev;
} t_raw_token;

typedef struct s_shell
{
    t_command *commands;
    char cwd[MAX_PATH];
	int *exit;
    int command_count;
} t_shell;

struct s_command {
    char *command;
    char *input;
    char **args;
    int arg_count;
    char *output;
    t_command *related_to;
    int relation_type; // 0 = delimiter, 1 = command, 2 = executable, 3 = argument, 4 = Assignment operator, 5 = redirect, 6 = pipe, -1 = error (not found)
    t_command *next;
    int is_internal; // 0 = Not internal, 1 = Is internal function
    t_token *input_redirection;
    t_token *output_redirection;
    t_token *append_redirection;
    t_token *heredoc_redirection;
    t_shell *shell;
};

//////////beta///////////
////////////////////////
void link_commands_and_tokens(t_token *tokens, t_command *cmd);
int fill_command_from_tokens(t_token *tokens, t_command **cmd);
void handle_pipes(t_command *cmd);
//////////filler/////////
/////////////////////

// Init:
void init_command(t_command *cmd);
void init_token(t_token *token, t_raw_token *t_raw_token);



t_raw_token* handle_input(char *input);

void print_raw_tokens(t_raw_token *first_token);

int identify_env_var(char *str);
t_token *allocate_token(int length);
void fill_token_fields(t_token *token, char *start, int length, int quote_state);
int is_command_expected(t_token *prev_token);
int check_unclosed_quotes(char *input);

t_token *convert_raw_token(t_raw_token *raw_token);
int is_raw_token_list_empty(t_raw_token *raw_token_head);
void link_token_to_list(t_token **new_head, t_token **current_new, t_token *new_token);
t_token *convert_raw_token_list(t_raw_token *raw_token_head);

t_token *process_token_list(t_token *token_list);
void assign_token_role(t_token *token_list);
void handle_command_token(t_token *token);
void handle_redirect_token(t_token *token);
void handle_pipe_token(t_token *token);


int validate_token_syntax(t_token *token_list);


void    print_token_list(t_token *token_list);

// Utils:
char *ft_strtok(char *str, const char *delimiters);
int ft_atoi(const char *str);
char *ft_strchr(const char *s, int c);
char *ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strtok_r(char *str, const char *delim, char **saveptr);
char *ft_strjoin_and_free(char *s1, char *s2);
int ft_strcmp(const char *s1, const char *s2);

int is_quote_char(char c);
int get_quote_type(char c);
int is_whitespace(char c);
int is_builtin_command(const char *cmd);
int is_redirection(char *str);
int is_pipe(char *str);
int is_special_char(char c);
char *ft_strndup(const char *s1, size_t n);
char *ft_strcpy(char *dst, const char *src);

// Input handling:

// Signal handling:
void setup_signal_handling();

// Freeing:
void free_command(t_command *cmd);
void free_commands(t_command *cmd);
void free_tokens(t_token *token);
void free_raw_tokens(t_raw_token *first_token);

#endif
