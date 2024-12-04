/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaumann <mnaumann@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:20:21 by mnaumann          #+#    #+#             */
/*   Updated: 2024/12/02 19:37:11 by mnaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef unsigned long long	t_size_t;

char *ft_strndup(const char *s1, size_t n)
{
    size_t i;
    char *s1cc;

	i = 0;
    s1cc = (char *)malloc((n + 1) * sizeof(char));
    if (s1cc == NULL)
    {
        return NULL;
    }
    while (i < n && s1[i] != '\0')
    {
        s1cc[i] = s1[i];
		i++;
    }
    s1cc[i] = '\0';
    return s1cc;
}

char *ft_strcpy(char *dst, const char *src)
{
    size_t i;

    i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return dst;
}

int is_pipe(char *str)
{
    return ft_strcmp(str, "|") == 0;
}

int identify_env_var(char *str)
{
    return *str == '$' && (*(str + 1) == '?' || 
           (*(str + 1) && !is_whitespace(*(str + 1))));
}
