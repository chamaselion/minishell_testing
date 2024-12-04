/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:49:26 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/17 16:30:18 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

void	*ft_memcpy(void *dst, const void *src, t_size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	t_size_t		i;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
	{
		return (0);
	}
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return (dst);
}
