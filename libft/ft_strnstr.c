/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:34:12 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/11 15:07:17 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

char	*ft_strnstr(const char *h, const char *n, t_size_t l)
{
	t_size_t		i;
	t_size_t		j;

	i = 0;
	if (n[0] == '\0')
	{
		return ((char *)h);
	}
	while (i < l && h[i] != '\0')
	{
		j = 0;
		while (i + j < l && n[j] != '\0' && n[j] == h[i + j])
		{
			j++;
		}
		if (n[j] == '\0')
		{
			return ((char *)h + i);
		}
		i++;
	}
	return (0);
}
