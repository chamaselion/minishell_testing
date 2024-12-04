
/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_free_and_exit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:09:32 by bszikora          #+#    #+#             */
/*   Updated: 2024/10/10 13:09:36 by bszikora         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void free_command(t_command *cmd)
{
    if (cmd->command)
        free(cmd->command);
    if (cmd->input)
        free(cmd->input);
    if (cmd->args)
    {
        for (int i = 0; i < cmd->arg_count; i++)
        {
            if (cmd->args[i])
                free(cmd->args[i]);
        }
        free(cmd->args);
    }
    if (cmd->output)
        free(cmd->output);
    if (cmd->input_redirection)
        free(cmd->input_redirection);
    if (cmd->output_redirection)
        free(cmd->output_redirection);
    if (cmd->append_redirection)
        free(cmd->append_redirection);
    if (cmd->heredoc_redirection)
        free(cmd->heredoc_redirection);
}

void free_commands(t_command *cmd)
{
    t_command *temp;

    while (cmd != NULL)
    {
        temp = cmd;
        cmd = cmd->next;
        free_command(temp);
        free(temp);
    }
}

int free_and_return(char *content, int ret)
{
    free(content);
    return ret;
}

int free_and_fail(char *content, char *message)
{
    free(content);
    ft_putstr_fd(message, STDERR_FILENO);
    return 0;
}

void free_tokens(t_token *token)
{
    t_token *current;
    t_token *next;

    current = token;
    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
}