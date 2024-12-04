/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:46:16 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/09 17:54:10 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

void	ft_bzero(void *str, t_size_t len)
{
	unsigned char	*ptr;
	t_size_t		i;

	ptr = str;
	i = 0;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
}
