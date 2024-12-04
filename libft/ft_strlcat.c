/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:33:43 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/09 18:50:42 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

t_size_t	ft_strlcat(char *restrict dst, const char *restrict src,
		t_size_t dstsize)
{
	t_size_t	i;
	t_size_t	j;
	t_size_t	l;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < dstsize)
	{
		i++;
	}
	l = i;
	while (src[j] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (l < dstsize)
		dst[i] = '\0';
	while (src[j] != '\0')
	{
		j++;
	}
	return (l + j);
}
