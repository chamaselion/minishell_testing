/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenizer2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaumann <mnaumann@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:12:59 by mnaumann          #+#    #+#             */
/*   Updated: 2024/12/04 18:13:52 by mnaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void categorize_token(t_token *token, int command_expected) 
{
    if (is_pipe(token->content))
        token->role = ROLE_PIPE;
    if (is_redirection(token->content))
        token->role = ROLE_REDIRECT;
    if (identify_env_var(token->content))
        token->role = ROLE_VARIABLE;
    if (command_expected) 
    {
        if (is_builtin_command(token->content))
            token->role = ROLE_BUILTIN;
        else if (is_executable(token->content))
            token->role = ROLE_EXECUTABLE;
    }
    if (token->prev && (token->prev->role == ROLE_BUILTIN || token->prev->role == ROLE_EXECUTABLE))
        token->role = ROLE_ARGUMENT;
    else
        token->role = ROLE_DEFAULT;
}*/


t_token *convert_raw_token(t_raw_token *raw_token) 
{
    t_token *new_token;
    if (raw_token == NULL) 
        return NULL;
    new_token = malloc(sizeof(t_token));
    if (new_token == NULL) 
        return NULL;
    new_token->content = ft_strdup(raw_token->segment);
    new_token->quote_state = raw_token->quote_state;
    new_token->position = raw_token->position;
    new_token->role = 0;
    new_token->command_expected = 0;
    new_token->next = NULL;
    new_token->prev = NULL;
    return new_token;
}

int is_raw_token_list_empty(t_raw_token *raw_token_head)
{
    if (raw_token_head == NULL)
        return (1);
    return (0);
}
void link_token_to_list(t_token **new_head, t_token **current_new, t_token *new_token)
{
    if (!(*new_head))
        *new_head = new_token;
    else 
    {
        (*current_new)->next = new_token;
        new_token->prev = *current_new;
    }
    *current_new = new_token;
}
t_token *convert_raw_token_list(t_raw_token *raw_token_head)
{    
    t_token *new_head;
    t_token *current_new;
    t_raw_token *current_raw;
    t_token *new_token;
    
    new_head = NULL;
    current_new = NULL;
    current_raw = raw_token_head;
    if (is_raw_token_list_empty(raw_token_head))
        return (NULL);
    while (current_raw != NULL) 
    {
        new_token = convert_raw_token(current_raw);
        if (new_token == NULL)
            return (NULL);
        link_token_to_list(&new_head, &current_new, new_token);
        current_raw = current_raw->next;
    }
    return (new_head);
}

