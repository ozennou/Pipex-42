/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:50:30 by mozennou          #+#    #+#             */
/*   Updated: 2023/11/30 21:37:15 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

size_t	ft_strlcpy(char *d, const char *s, unsigned int n)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(s);
	if (n > 0)
	{
		while (s[i] != '\0' && i < n - 1)
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
	}
	return (len);
}

char	*ft_strjoin(char const *a, char const *b)
{
	int		i;
	int		a_ln;
	int		b_ln;
	char	*res;

	if (!a || !b)
		return (NULL);
	a_ln = ft_strlen((char *)a);
	b_ln = ft_strlen((char *)b);
	res = (char *)malloc(a_ln + b_ln + 1);
	if (!res)
		return (res);
	i = -1;
	while (++i < a_ln)
		res[i] = a[i];
	i = -1;
	while (++i < b_ln)
		res[a_ln + i] = b[i];
	res[a_ln + i] = '\0';
	return (res);
}

char	*check(char **path, char *cmd)
{
	int		i;
	char	*res;

	i = -1;
	while (path[++i])
	{
		res = ft_strdup(cmd);
		if (!ft_strncmp(path[i], res, ft_strlen(path[i])))
			return (res);
		free(res);
	}
	return (NULL);
}

char	*get_cmd(char *cmd, char **path)
{
	char	*res;
	int		i;

	i = -1;
	set_path(path);
	res = check(path, cmd);
	if (res)
		return (res);
	while (path[++i])
	{
		res = ft_strjoin(path[i], cmd);
		if (!access(res, F_OK))
			return (res);
		free(res);
	}
	res = ft_strdup(cmd);
	if (access(res, F_OK) == 0)
		return (res);
	free(res);
	return (NULL);
}
