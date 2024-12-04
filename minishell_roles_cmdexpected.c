/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_roles_cmdexpected.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaumann <mnaumann@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:28:30 by mnaumann          #+#    #+#             */
/*   Updated: 2024/12/04 18:39:47 by mnaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_first_token(t_token *token)
{
    token->role = ROLE_EXECUTABLE;
    token->command_expected = 1;
}

void handle_quote_token(t_token *token)
{
    token->role = ROLE_DELIMITER;
}

void handle_pipe_token(t_token *token)
{
    token->role = ROLE_PIPE;
    if (token->next)
        token->next->command_expected = 1;
}

void handle_redirect_token(t_token *token)
{
    token->role = ROLE_REDIRECT;
    token->command_expected = 0;
}

void assign_token_role(t_token *token_list)
{
    t_token *current = token_list;

    if (current)
        handle_first_token(current);

    while (current)
    {
        if (is_quote_char(*current->content))
            handle_quote_token(current);
        else if (is_pipe(current->content))
            handle_pipe_token(current);
        else if (is_redirection(current->content))
            handle_redirect_token(current);
        else if (identify_env_var(current->content))
            current->role = ROLE_VARIABLE;
        else if (current->prev && 
                 (is_quote_char(*current->prev->content) ||
                  current->prev->role == ROLE_EXECUTABLE || 
                  current->prev->role == ROLE_ARGUMENT))
            current->role = ROLE_ARGUMENT;
        else
            current->role = ROLE_EXECUTABLE;
        current = current->next;
    }
}
void    print_token_list(t_token *token_list)
{
    t_token *current = token_list;
    while (current != NULL)
    {
        printf("Token: %s, Role: %d, Command Expected: %d\n", current->content, current->role, current->command_expected);
        current = current->next;
    }
}