/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:53:30 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/14 16:10:22 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*r;
	unsigned int	c;
	unsigned int	l;

	c = 0;
	l = ft_strlen(s);
	r = (char *)malloc(sizeof(char) * (l + 1));
	if (r == 0)
		return (0);
	while (c < l)
	{
		r[c] = f(c, s[c]);
		c++;
	}
	r[c] = '\0';
	return (r);
}
