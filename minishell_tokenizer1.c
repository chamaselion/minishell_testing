/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenizer1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaumann <mnaumann@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:23:34 by mnaumann          #+#    #+#             */
/*   Updated: 2024/12/04 18:16:00 by mnaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_raw_token *create_raw_token(char *segment, t_quote_state quote_state, int position) 
{
    t_raw_token *token = malloc(sizeof(t_raw_token));
    token->segment = ft_strdup(segment);
    token->quote_state = quote_state;
    token->position = position;
    token->next = NULL;
    token->prev = NULL;
    return token;
}

void append_raw_token(t_raw_token **first, t_raw_token **last, t_raw_token *new_token) 
{
    if (!*first) 
    {
        *first = new_token;
        *last = new_token;
        return;
    }
    (*last)->next = new_token;
    new_token->prev = *last;
    *last = new_token;
}

char *skip_whitespace(char *input) 
{
	while (*input && is_whitespace(*input)) 
	{
		input++;
	}
	return input;
}

int is_valid_env_var_name(const char *str) {
    if (!str || !*str) 
        return 0;
    if (!ft_isalpha(*str) && *str != '_') 
        return 0;
    while (*++str) 
    {
        if (!ft_isalnum(*str) && *str != '_') 
        return 0;
    }
    
    return 1;
}

char* expand_env_variable(const char *var_name) 
{
    if (!var_name) return NULL;
    return getenv(var_name);
}

t_raw_token *handle_non_quote_segment(const char **input, int *pos) 
{
    const char *start = *input;
    while (**input && !is_whitespace(**input) && !is_quote_char(**input)) 
        (*input)++;
    char *segment = ft_strndup(start, *input - start);
    t_raw_token *token = create_raw_token(segment, NO_QUOTE, *pos);
    free(segment);
    
    return token;
}

t_raw_token* handle_single_quote_segment(const char **input, int *pos) 
{
    t_raw_token *first = NULL;
    t_raw_token *last = NULL;
    const char *content_start = *input;
    
    char quote_str[2] = {'\'', '\0'};
    append_raw_token(&first, &last, 
        create_raw_token(quote_str, NO_QUOTE, *pos));
    (*input)++;
    (*pos)++;    
    while (**input && **input != '\'') 
        (*input)++;
    if (*input > content_start) 
    {
        char *content = strndup(content_start, *input - content_start);
        append_raw_token(&first, &last, 
            create_raw_token(content, WITHIN_SINGLE_QUOTE, *pos));
        free(content);
    }
    if (**input) 
    {
        append_raw_token(&first, &last, 
            create_raw_token(quote_str, NO_QUOTE, *pos));
        (*input)++;
    }
    return first;
}

char* expand_double_quote_variables(const char *content) 
{
    char expanded[1024] = {0};
    char *write_ptr = expanded;
    char var_name[256] = {0};
    int var_idx = 0;
    
    while (*content) 
    {
        if (*content == '$') 
        {
            content++;            
            while (ft_isalnum(*content) || *content == '_')
                var_name[var_idx++] = *content++;
            if (is_valid_env_var_name(var_name)) 
            {
                char *env_value = expand_env_variable(var_name);
                if (env_value) 
                {
                    ft_strcpy(write_ptr, env_value);
                    write_ptr += ft_strlen(env_value);
                }
            } 
            else 
            {
                *write_ptr++ = '$';
                ft_strcpy(write_ptr, var_name);
                write_ptr += ft_strlen(var_name);
            }
        } 
        else 
            *write_ptr++ = *content++;
    }
    *write_ptr = '\0';
    return ft_strdup(expanded);
}

t_raw_token* handle_double_quote_segment(const char **input, int *pos) 
{
    t_raw_token *first = NULL;
    t_raw_token *last = NULL;
    
    char quote_str[2] = {'"', '\0'};
    append_raw_token(&first, &last, 
        create_raw_token(quote_str, NO_QUOTE, *pos));
    (*input)++;
    (*pos)++;
    const char *content_start = *input;
    
    while (**input && **input != '"') 
        (*input)++;
    if (*input > content_start) 
    {
        char *content = ft_strndup(content_start, *input - content_start);
        char *expanded_content = expand_double_quote_variables(content);
        append_raw_token(&first, &last, 
            create_raw_token(expanded_content, WITHIN_DOUBLE_QUOTE, *pos));
        free(content);
        free(expanded_content);
    }
    if (**input) 
    {
        append_raw_token(&first, &last, 
            create_raw_token(quote_str, NO_QUOTE, *pos));
        (*input)++;
    }
    return first;
}

t_raw_token* handle_input(char *input) 
{
    t_raw_token *first = NULL;
    t_raw_token *last = NULL;
    int pos = 0;
    
    while (*input) 
    {
        input = (char *)skip_whitespace(input);
        pos++;
        if (*input == '\'') 
        {
            t_raw_token *quote_tokens = handle_single_quote_segment((const char **)&input, &pos);
            while (quote_tokens) 
            {
                t_raw_token *next = quote_tokens->next;
                append_raw_token(&first, &last, quote_tokens);
                quote_tokens = next;
            }
            continue;
        }
        if (*input == '"') 
        {
            t_raw_token *quote_tokens = handle_double_quote_segment((const char **)&input, &pos);
            while (quote_tokens) 
            {
                t_raw_token *next = quote_tokens->next;
                append_raw_token(&first, &last, quote_tokens);
                quote_tokens = next;
            }
            continue;
        }
        t_raw_token *segment_token = handle_non_quote_segment((const char **)&input, &pos);
        append_raw_token(&first, &last, segment_token);
    }
    return first;
}

void print_raw_tokens(t_raw_token *first_token) 
{
    int count = 0;
    while (first_token) 
    {
        printf("Token %d: '%s' (Quote State: %d, Position: %d)\n", 
               count++, 
               first_token->segment, 
               first_token->quote_state, 
               first_token->position);
        first_token = first_token->next;
    }
}

void free_raw_tokens(t_raw_token *first_token) 
{
    while (first_token) 
    {
        t_raw_token *temp = first_token;
        first_token = first_token->next;
        free(temp->segment);
        free(temp);
    }
}


//Debugging main function
/*int main() {
    char *input = "echo \" khef $HOME\" | pwd | echo \" haloo 20$ OME\" | echo \" haloo 20$HOME\" | echo 'safdh $ORG *\"'";
    t_raw_token *tokens = advanced_tokenization(input);
    print_raw_tokens(tokens);
    free_raw_tokens(tokens);
    return 0;
}*/
