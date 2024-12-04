/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:15:26 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/15 15:47:22 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

typedef unsigned long long	t_size_t;

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*r;
	t_size_t	c;
	t_size_t	c1;

	c = 0;
	c1 = 0;
	if (!s1 || !s2)
		return (NULL);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r)
		return (NULL);
	while (s1[c] != '\0')
	{
		r[c] = s1[c];
		c++;
	}
	while (s2[c1] != '\0')
	{
		r[c + c1] = s2[c1];
		c1++;
	}
	r[c + c1] = '\0';
	return (r);
}
