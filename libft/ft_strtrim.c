/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:54:22 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/15 15:40:44 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

typedef unsigned long long	t_size_t;

char	*handle_null_character(void)
{
	char	*r;

	r = (char *)malloc(1);
	if (r == NULL)
		return (NULL);
	*r = '\0';
	return (r);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*r;
	int			start;
	int			end;
	t_size_t	tlength;

	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != 0)
		start++;
	if (s1[start] == '\0')
	{
		return (handle_null_character());
	}
	while (end >= start && ft_strchr(set, s1[end]) != 0)
		end--;
	tlength = end - start + 1;
	r = (char *)malloc(tlength + 1);
	if (r == 0)
		return (0);
	ft_strlcpy(r, s1 + start, tlength + 1);
	r[tlength] = '\0';
	return (r);
}
