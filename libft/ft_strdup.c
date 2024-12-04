/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:36:22 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/08 18:58:25 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef unsigned long long	t_size_t;

char	*ft_strdup(const char *s1)
{
	t_size_t	l;
	t_size_t	i;
	const char	*s1c;
	char		*s1cc;

	l = 0;
	i = 0;
	s1c = s1;
	while (s1c[l] != '\0')
	{
		l++;
	}
	s1cc = (char *)malloc((l + 1) * sizeof(char));
	if (s1cc == 0)
	{
		return (0);
	}
	while (i < l)
	{
		s1cc[i] = s1c[i];
		i++;
	}
	s1cc[l] = '\0';
	return (s1cc);
}
