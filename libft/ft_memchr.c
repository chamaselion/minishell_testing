/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:44:42 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/17 16:38:35 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

void	*ft_memchr(const void *s, int c, t_size_t n)
{
	t_size_t			i;
	const unsigned char	*s1;
	unsigned char		s2;

	i = 0;
	s1 = s;
	s2 = (unsigned char)c;
	while (i < n)
	{
		if (s1[i] == s2)
		{
			return ((void *)&s1[i]);
		}
		i++;
	}
	return (0);
}
