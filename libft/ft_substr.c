/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:03:08 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/11 18:11:45 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

typedef unsigned long long	t_size_t;

char	*ft_substr(char const *s, unsigned int start, t_size_t len)
{
	t_size_t	i;
	t_size_t	c;
	char		*r;

	i = start;
	c = 0;
	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
	{
		len = 0;
		start = ft_strlen(s);
	}
	else if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	r = (char *)malloc(sizeof(char) * (len + 1));
	if (r == 0)
		return (0);
	i = start;
	c = 0;
	while (s[i] != '\0' && c < len)
		r[c++] = s[i++];
	r[c] = '\0';
	return (r);
}
