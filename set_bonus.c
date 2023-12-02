/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:42:06 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 09:35:07 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_data(t_data *data, int l)
{
	int	i;
	int	j;

	i = 0;
	if (l >= 1)
	{
		while (data->paths[i])
			free(data->paths[i++]);
		free(data->paths);
	}
	if (l >= 2)
	{
		i = 0;
		while (i < data->nbr_cmd)
		{
			j = 0;
			while (data->split_cmds[i][j])
				free(data->split_cmds[i][j++]);
			free(data->split_cmds[i]);
			i++;
		}
		free(data->split_cmds);
	}
	if (l >= 3)
		free(data->path_cmds);
}

int	test(t_data *data)
{
	int	i;

	i = 0;
	data->pipefd = malloc(sizeof (int *) * (data->nbr_cmd + 1));
	if (!data->pipefd)
		return (free_data(data, 3), 1);
	while (i < data->nbr_cmd)
	{
		if (data->split_cmds[i][0])
			data->path_cmds[i] = get_cmd(data->split_cmds[i][0], data->paths);
		else
			data->path_cmds[i] = NULL;
		i++;
	}
	return (0);
}

int	params(t_data *data)
{
	if (data->here_doc)
		return (3);
	else
		return (2);
}

int	set_data(char **av, char **env, t_data *data)
{
	int	i;
	int	l;

	i = 0;
	data->paths = ft_split(get_path(env), ':');
	if (!data->paths)
		return (1);
	l = params(data);
	data->split_cmds = malloc(sizeof (char **) * (data->nbr_cmd + 1));
	if (!data->split_cmds)
		return (free_data(data, 1), 1);
	while (i < data->nbr_cmd)
	{
		data->split_cmds[i] = my_split(av[i + l]);
		i++;
	}
	data->path_cmds = malloc(sizeof (char *) * (data->nbr_cmd + 1));
	if (!data->path_cmds)
		return (free_data(data, 2), 1);
	if (test(data))
		return (1);
	return (0);
}
