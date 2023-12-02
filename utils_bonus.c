/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:48:24 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 09:34:39 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*pp;

	if (!s && !d)
		return (NULL);
	i = 0;
	p = (unsigned char *)d;
	pp = (unsigned char *)s;
	while (i < n)
	{
		p[i] = pp[i];
		i++;
	}
	return (d);
}

static int	cw(char const *s, char c)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			res++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (res);
}

int	func2(const char **s, char c)
{
	int	res;

	while (**s && **s == c)
		(*s)++;
	res = 0;
	while ((*s)[res] && (*s)[res] != c)
		res++;
	return (res);
}

static char	**ft_free(char **res, int l)
{
	while (l >= 0)
		free(res[l--]);
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		l;

	if (!s)
		return (NULL);
	l = 0;
	res = (char **)malloc(sizeof(char *) * (cw(s, c) + 1));
	if (res == NULL)
		return (NULL);
	while (*s)
	{
		i = func2(&s, c);
		if (i > 0)
		{
			res[l] = (char *)malloc((i + 1) * sizeof(char));
			if (!res[l])
				return (ft_free(res, l - 1));
			ft_memcpy(res[l], s, i);
			res[l++][i] = '\0';
			s += i;
		}
	}
	res[l] = 0;
	return (res);
}
