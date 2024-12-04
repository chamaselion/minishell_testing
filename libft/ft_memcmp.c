/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:23:11 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/09 17:53:55 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

int	ft_memcmp(const void *s1, const void *s2, t_size_t n)
{
	t_size_t			i;
	const unsigned char	*st1;
	const unsigned char	*st2;

	i = 0;
	st1 = (const unsigned char *)s1;
	st2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (st1[i] != st2[i])
		{
			return ((st1[i] - st2[i]));
		}
		i++;
	}
	return (0);
}
