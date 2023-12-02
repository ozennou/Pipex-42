/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:01:01 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 10:29:53 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit(1);
}

int	checkerror(char **av, int ac)
{
	int	l;

	l = 0;
	if (access(av[1], R_OK))
	{
		my_perror("pipex: ", av[1]);
		my_perror(": permission denied\n", NULL);
		l++;
	}
	if (!access(av[ac - 1], F_OK) && access(av[ac - 1], W_OK))
	{
		my_perror("pipex: ", av[ac - 1]);
		my_perror(": permission denied\n", NULL);
		l++;
	}
	if (l)
		return (1);
	return (0);
}

void	ft_open(int ac, char **av, t_data *data)
{
	if (data->here_doc)
		data->fdin = read_heredoc(data->limiter, data);
	else
		data->fdin = open(av[1], O_RDONLY);
	if (data->here_doc)
		data->fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fdout == -1)
		ft_error(data);
}

void	ft_error(t_data *data)
{
	perror(strerror(errno));
	ft_free2(data);
	exit(1);
}

void	set_path(char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/')
		{
			tmp = path[i];
			tmp = ft_strjoin(path[i], "/"); 
			free(path[i]);
			path[i] = tmp;
		}
		i++;
	}
}
