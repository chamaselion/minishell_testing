/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:24:00 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/08 18:35:48 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef unsigned long long	t_size_t;

void	*ft_calloc(t_size_t count, t_size_t size)
{
	t_size_t	i;
	t_size_t	ts;
	void		*ptr;

	ts = count * size;
	ptr = malloc(ts);
	i = 0;
	if (ptr == 0)
	{
		return (0);
	}
	while (i < ts)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
