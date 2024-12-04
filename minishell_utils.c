/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaumann <mnaumann@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:12:45 by root              #+#    #+#             */
/*   Updated: 2024/12/04 17:45:14 by mnaumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strtok_r(char *str, const char *delim, char **saveptr)
{
    char *end;

    if (str == NULL)
        str = *saveptr;
    while (*str && ft_strchr(delim, *str))
        str++;
    if (*str == '\0')
    {
        *saveptr = str;
        return (NULL);
    }
    end = str;
    while (*end && !ft_strchr(delim, *end))
        end++;
    if (*end == '\0')
    {
        *saveptr = end;
        return (str);
    }
    *end = '\0';
    *saveptr = end + 1;
    return (str);
}

char *ft_strtok(char *str, const char *delim)
{
    static char *last;

    return (ft_strtok_r(str, delim, &last));
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}

int ft_itoa_base(int value, int base, char *buffer, int size)
{
    char *digits = "0123456789abcdef";
    char tmp[32];
    int i = 0, j = 0;
    int negative = 0;

    if (value < 0)
    {
        negative = 1;
        value = -value;
    }

    do
    {
        tmp[i++] = digits[value % base];
        value /= base;
    } while (value && i < 32);

    if (negative && j < size - 1)
        buffer[j++] = '-';

    while (i > 0 && j < size - 1)
        buffer[j++] = tmp[--i];

    buffer[j] = '\0';
    return j;
}

char *ft_strjoin_and_free(char *s1, char *s2)
{
    char *result;

    result = ft_strjoin(s1, s2);
    free(s1);
    return result;
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t i;

    i = 0;
    while ((unsigned char)s1[i] && (unsigned char)s1[i] == (unsigned char)s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
