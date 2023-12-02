/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 07:35:53 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 09:58:00 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t n, size_t s)
{
	void			*res;
	size_t			i;
	unsigned char	*p;

	res = malloc(n * s);
	if (!res)
		return (NULL);
	i = 0;
	p = (unsigned char *)res;
	while (i < n * s)
		p[i++] = '\0';
	return (res);
}
