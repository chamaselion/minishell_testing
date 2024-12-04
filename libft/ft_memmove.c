/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:59:34 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/09 16:54:29 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef unsigned long long	t_size_t;

void	ft_norminettebs(unsigned char *pdst, const unsigned char *psrc,
		t_size_t len)
{
	t_size_t	i;

	i = 0;
	while (i < len)
	{
		pdst[i] = psrc[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, t_size_t len)
{
	unsigned char	*pdst;
	unsigned char	*psrc;
	t_size_t		i;

	pdst = (unsigned char *) dst;
	psrc = (unsigned char *) src;
	i = 0;
	if (pdst == psrc)
		return (dst);
	if (pdst < psrc)
	{
		ft_norminettebs(pdst, psrc, len);
	}
	else
	{
		i = len;
		while (i > 0)
		{
			pdst[i - 1] = psrc[i - 1];
			i--;
		}
	}
	return (dst);
}
