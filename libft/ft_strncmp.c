/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:31:59 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/16 16:29:59 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

int	ft_strncmp(const char *s1, const char *s2, t_size_t n)
{
	t_size_t	i;

	i = 0;
	if (!n)
	{
		return (0);
	}
	while (--n > 0 && s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	if ((unsigned char)s1[i] > (unsigned char)s2[i])
	{
		return (1);
	}
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
	{
		return (-1);
	}
	return (0);
}
