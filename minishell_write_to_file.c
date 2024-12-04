/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_write_to_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaumann <mnaumann@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:09:48 by bszikora          #+#    #+#             */
/*   Updated: 2024/11/29 11:46:22 by mnaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_parsed_input_to_file(t_parsed_input *parsed_input, const char *filename)
{
    int fd;
    int i = 0;
    char buffer[1024];
    int len;
    t_token *current_token;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("Error opening file\n", STDERR_FILENO);
        return;
    }
    current_token = parsed_input->token;
    while (current_token)
    {
        write(fd, current_token->start, current_token->length);
        if (parsed_input->special_char[i].count >= 1)
        {
            len = snprintf(buffer, sizeof(buffer), " (Special: %d)", parsed_input->special_char[i].type);
            write(fd, buffer, len);
        }
        write(fd, "\n", 1);
        current_token = current_token->next;
        i++;
    }
    write(fd, "---\n", 4);  // Separator between commands
    close(fd);
}
