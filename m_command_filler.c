#include "minishell.h"

t_command* create_new_command()
{
    t_command *new_cmd;
	
	new_cmd = (t_command*)malloc(sizeof(t_command));
    if (new_cmd == NULL)
        return (NULL);
    new_cmd->command = NULL;
    new_cmd->input = NULL;
    new_cmd->args = NULL;
    new_cmd->arg_count = 0;
    new_cmd->output = NULL;
    new_cmd->related_to = NULL;
    new_cmd->relation_type = 0;
    new_cmd->next = NULL;
    new_cmd->is_internal = 0;
    new_cmd->input_redirection = NULL;
    new_cmd->output_redirection = NULL;
    new_cmd->append_redirection = NULL;
    new_cmd->heredoc_redirection = NULL;
    return (new_cmd);
}

int	expected_command_counter(t_token *token)
{
	t_token *current_token;
	int c;

	current_token = token;
	c = 0;

	while (current_token)
	{
		if (current_token->role == 1 || current_token->role == 2)
			c++;
		current_token = current_token->next;
	}
	return (c);
}

t_command* create_command_list(t_token *tokens)
{
    int command_count;
    int c;
    t_command *current_command;
	t_command *head;

    command_count = expected_command_counter(tokens);
    head = create_new_command();
    if (head == NULL)
        return (NULL);
    current_command = head;
    c = 1;
    while (c < command_count)
	{
        current_command->next = create_new_command();
        if (current_command->next == NULL)
            return (NULL);
        current_command = current_command->next;
        c++;
    }
	return (head);
}

int allocate_args(t_command *current_cmd, t_token *ct)
{
    current_cmd->args = realloc(current_cmd->args, sizeof(char*) * (current_cmd->arg_count + 1));
    if (current_cmd->args == NULL)
	{
        return (-1);
    }
    current_cmd->args[current_cmd->arg_count] = ct->content;
    current_cmd->arg_count++;
    return (0);
}

void remove_last_empty_command(t_command *head_cmd, t_command *current_cmd)
{
	t_command *prev_cmd;

    if (current_cmd->command == NULL && current_cmd->args == NULL)
	{
        prev_cmd = head_cmd;
        while (prev_cmd->next != current_cmd)
		{
            prev_cmd = prev_cmd->next;
        }
        prev_cmd->next = NULL;
        free(current_cmd);
    }
}

int process_tokens(t_token *ct, t_command *current_cmd)
{
    while (ct && (ct->role == 3 || ct->role == 0))
	{
        if (ct->role == 3)
		{
            if (allocate_args(current_cmd, ct) == -1)
                return (-1);
        }
        ct = ct->next;
    }
    current_cmd->args = realloc(current_cmd->args, sizeof(char*) * (current_cmd->arg_count + 1));
    if (current_cmd->args == NULL)
        return (-1);
    current_cmd->args[current_cmd->arg_count] = NULL;
    return (0);
}

int fill_command_from_tokens(t_token *tokens, t_command **cmd)
{
    t_token *ct;
    t_command *current_cmd;
    t_command *head_cmd;

    ct = tokens;
    head_cmd = create_command_list(tokens);
    if (head_cmd == NULL)
        return (-1);
    current_cmd = head_cmd;
    *cmd = head_cmd;
    while (ct)
	{
        if (ct->role == 1 || ct->role == 2)
		{
            current_cmd->command = ct->content;
            ct = ct->next;
            if (process_tokens(ct, current_cmd) == -1)
                return (-1);
            if (current_cmd->next)
                current_cmd = current_cmd->next;
        }
		else
            ct = ct->next;
    }
	if (current_cmd != NULL)
    {
        current_cmd->next = NULL;
    }
    return (expected_command_counter(tokens));
}

void link_commands_and_tokens(t_token *tokens, t_command *cmd)
{
    t_token *ct = tokens;
    t_command *current_cmd;
	
	current_cmd = cmd;

    while (ct)
	{
        if (ct->role == 4)
		{
        }
		else if (ct->role == 5)
		{ // Redirect
            if (strcmp(ct->content, ">") == 0)
                current_cmd->output_redirection = ct->next;
			else if (strcmp(ct->content, "<") == 0)
                current_cmd->input_redirection = ct->next;
			else if (strcmp(ct->content, ">>") == 0)
                current_cmd->append_redirection = ct->next;
			else if (strcmp(ct->content, "<<") == 0)
                current_cmd->heredoc_redirection = ct->next;
            ct = ct->next;
			current_cmd->relation_type = 5;
        }
		else if (ct->role == 6)
		{ // Pipe
            if (current_cmd->next)
			{
                current_cmd->relation_type = 6; // Pipe
                current_cmd->related_to = current_cmd->next;
                current_cmd = current_cmd->next;
            }
        }
        ct = ct->next;
    }
}

/*
	while (commands)
	{
		printf("Command[%i]: %s, args: %s, relation type: %i\n", i, commands->command, commands->args[0], commands->relation_type);
		commands = commands->next;
		i++;
	}
*/