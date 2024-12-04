#include "minishell.h"


void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, strlen(s));
}

void handle_ft_command(t_command *cmd)
{
	(void)cmd;
   /* if (strcmp(cmd->command, "cd") == 0)
        ft_cd(cmd);
	if (strcmp(cmd->command, "echo") == 0)
        ft_echo(cmd);
	if (strcmp(cmd->command, "exit") == 0)
        ft_exit(cmd);
	if (strcmp(cmd->command, "export") == 0)
        ft_export(cmd);
	if (strcmp(cmd->command, "pwd") == 0)
        ft_pwd(cmd);*/
}

char *search_command(const char *command)
{
	char *path;
	char *dir;
	char full_path[4096];
	char *result;
	char *path_env;
	
	path_env = getenv("PATH");
	if (!path_env)
		return (ft_putstr_fd("Error", STDERR_FILENO), NULL);
	path = strdup(path_env);
	if (!path)
		return (ft_putstr_fd("Error", STDERR_FILENO), NULL);
	dir = strtok(path, ":");
	while (dir != NULL)
	{
        strcpy(full_path, dir);
        strcat(full_path, "/");
        strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
			return (result = strdup(full_path), free(path), result);
		dir = strtok(NULL, ":");
	}
	return (free(path), NULL);
}

void handle_input_redirection(t_command *cmd)
{
    int fd;
    if (cmd->input_redirection)
    {
        fd = open(cmd->input_redirection->content, O_RDONLY);
        if (fd == -1)
        {
            perror("open input redirection");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 input redirection");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
}

void handle_output_redirection(t_command *cmd)
{
    int fd;
    if (cmd->output_redirection)
    {
        fd = open(cmd->output_redirection->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("open output redirection");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 output redirection");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
}

void handle_append_redirection(t_command *cmd)
{
    int fd;
    if (cmd->append_redirection)
    {
        fd = open(cmd->append_redirection->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("open append redirection");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 append redirection");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
}

void handle_pipe_redirection(t_command *cmd, int pipefd[2])
{
    if (cmd->related_to != NULL && cmd->relation_type == 6)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
}

void handle_heredoc_redirection(t_command *cmd)
{
    int fd;
    if (cmd->heredoc_redirection)
    {
        fd = open(cmd->heredoc_redirection->content, O_RDONLY);
        if (fd == -1)
        {
            perror("open heredoc redirection");
            exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 heredoc redirection");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
}

void setup_redirection(t_command *cmd, int in_fd, int pipefd[2])
{
    handle_input_redirection(cmd);
    if (!cmd->input_redirection && in_fd != 0)
    {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    handle_output_redirection(cmd);
    handle_append_redirection(cmd);
    handle_pipe_redirection(cmd, pipefd);
    handle_heredoc_redirection(cmd);
}

char **construct_exec_args(t_command *cmd)
{
    char **exec_args;
	int c;

	c = 0;
	exec_args = malloc((cmd->arg_count + 2) * sizeof(char *));
    if (!exec_args)
    {
        ft_putstr_fd("Error", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    exec_args[0] = cmd->command;
    while (c < cmd->arg_count)
    {
        exec_args[c + 1] = cmd->args[c];
		c++;
    }
    exec_args[cmd->arg_count + 1] = NULL;
    return exec_args;
}

void execute_command(t_command *cmd, char **exec_args)
{
    char *full_path;
	
	full_path = search_command(cmd->command);
    if (full_path)
    {
        execve(full_path, exec_args, NULL);
        ft_putstr_fd("Error", STDERR_FILENO);
        free(full_path);
        free(exec_args);
        exit(EXIT_FAILURE);
    }
    else
    {
        ft_putstr_fd("Error", STDERR_FILENO);
        free(exec_args);
        exit(EXIT_FAILURE);
    }
}

void create_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
    {
        ft_putstr_fd("Error", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
}

pid_t fork_process()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        ft_putstr_fd("Error", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    return pid;
}

void handle_child_process(t_command *cmd, int in_fd, int pipefd[2])
{
	char **exec_args;
    if (cmd == NULL)
    {
        fprintf(stderr, "Error: cmd is NULL in handle_child_process\n");
        exit(EXIT_FAILURE);
    }
    exec_args = construct_exec_args(cmd);
    if (exec_args == NULL)
    {
        fprintf(stderr, "Error: Failed to construct exec args\n");
        exit(EXIT_FAILURE);
    }
    setup_redirection(cmd, in_fd, pipefd);
    if (cmd->is_internal)
    {
        handle_ft_command(cmd);
        exit(0);
    }
    else
        execute_command(cmd, exec_args);
}

void handle_parent_process(t_command *cmd, int *in_fd, int pipefd[2])
{
    if (cmd == NULL)
    {
        fprintf(stderr, "Error: cmd is NULL in handle_parent_process\n");
        return;
    }
    int status;
    if (*in_fd != 0)
        close(*in_fd);
    if (cmd->relation_type == 6 && cmd->related_to != NULL)
    {
        close(pipefd[1]);
        *in_fd = pipefd[0];
    }
    else
    {
        *in_fd = 0;
    }
    waitpid(-1, &status, 0);
}

void handle_pipes(t_command *cmd)
{
    int pipefd[2];
    pid_t pid;
    int in_fd = 0;

    if (cmd == NULL)
    {
        fprintf(stderr, "Error: cmd is NULL in handle_pipes\n");
        return;
	}
    while (cmd != NULL)
    {
        if (cmd->relation_type == 6 && cmd->related_to != NULL)
        {
            create_pipe(pipefd);
        }
        pid = fork_process();
        if (pid == 0)
        {
            handle_child_process(cmd, in_fd, pipefd);
        }
        else
        {
            handle_parent_process(cmd, &in_fd, pipefd);
        }
        cmd = cmd->related_to;
    }
}
