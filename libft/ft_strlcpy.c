/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:15:10 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/11 14:52:55 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

t_size_t	ft_strlcpy(char *restrict dst, const char *restrict src,
		t_size_t dstsize)
{
	t_size_t	i;
	t_size_t	l;
	t_size_t	length;

	i = 0;
	l = 0;
	length = 0;
	while (src[length] != '\0')
	{
		length++;
	}
	if (dstsize == 0)
		return (length);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[l] != '\0')
	{
		l++;
	}
	return (l);
}
