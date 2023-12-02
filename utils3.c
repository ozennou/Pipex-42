/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:03:57 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 12:44:05 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *a, const char *b, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*pp;

	i = 0;
	p = (unsigned char *)a;
	pp = (unsigned char *)b;
	while (i < n && (p[i] || pp[i]))
	{
		if (p[i] != pp[i])
			return (p[i] - pp[i]);
		i++;
	}
	return (0);
}

char	*get_path(char **env)
{
	while (*env != NULL)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			return (*env + 5);
		env++;
	}
	my_perror("PATH not found\n", NULL);
	return (NULL);
}

int	set_data(char **av, char **env, t_data *data)
{
	int	i;

	i = 0;
	data->paths = ft_split(get_path(env), ':');
	if (!data->paths)
		return (1);
	data->split_cmd1 = my_split(av[2]);
	data->split_cmd2 = my_split(av[3]);
	if (data->split_cmd1[0])
		data->path_cmd1 = get_cmd(data->split_cmd1[0], data->paths);
	else
		data->path_cmd1 = NULL;
	if (data->split_cmd2[0])
		data->path_cmd2 = get_cmd(data->split_cmd2[0], data->paths);
	else
		data->path_cmd2 = NULL;
	return (0);
}

void	ft_free2(t_data *data)
{
	int	i;

	if (data->split_cmd1)
	{
		i = 0;
		while (data->split_cmd1[i])
			free(data->split_cmd1[i++]);
		free(data->split_cmd1);
	}
	if (data->split_cmd2)
	{
		i = 0;
		while (data->split_cmd2[i])
			free(data->split_cmd2[i++]);
		free(data->split_cmd2);
	}
	free(data->path_cmd1);
	free(data->path_cmd2);
	i = 0;
	while (data->paths[i])
		free(data->paths[i++]);
	free(data->paths);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
