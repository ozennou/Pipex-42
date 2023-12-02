/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:03:57 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/01 09:56:50 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_free2(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nbr_cmd)
	{
		j = 0;
		while (data->split_cmds[i][j])
			free(data->split_cmds[i][j++]);
		free(data->split_cmds[i]);
		free(data->path_cmds[i]);
		i++;
	}
	i = 0;
	while (i < data->nbr_cmd - 1)
		free(data->pipefd[i++]);
	free(data->split_cmds);
	free(data->pipefd);
	free(data->path_cmds);
	i = 0;
	while (data->paths[i])
		free(data->paths[i++]);
	free(data->paths);
	free(data->pid);
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
	exit(1);
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
