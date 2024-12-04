/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_syntax_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaumann <mnaumann@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:01:33 by mnaumann          #+#    #+#             */
/*   Updated: 2024/12/04 15:08:02 by mnaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validate_token_syntax(t_token *token_list)
{
    t_token *current;
	
	current = token_list;
    while (current != NULL)
    {
        if (current->role == ROLE_PIPE && 
            (!current->prev || current->prev->role == ROLE_PIPE))
            return SYNTAX_ERROR;
        if (current->role == ROLE_REDIRECT && 
            (!current->next || current->next->role != ROLE_ARGUMENT))
            return SYNTAX_ERROR;
        current = current->next;
    }
    return SYNTAX_VALID;
}
