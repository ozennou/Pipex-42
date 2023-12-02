/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:46:58 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 10:27:19 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	my_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	set_child(t_data *data, int i)
{
	if (i == 0)
	{
		my_close(&data->pipefd[i][0]);
		ft_dup2(data->fdin, STDIN_FILENO);
		if (data->nbr_cmd == 1)
			ft_dup2(data->fdout, STDOUT_FILENO);
		else
			ft_dup2(data->pipefd[i][1], STDOUT_FILENO);
	}
	else if (i == data->nbr_cmd - 1)
	{
		my_close(&data->pipefd[i - 1][1]);
		ft_dup2(data->pipefd[i - 1][0], STDIN_FILENO);
		ft_dup2(data->fdout, STDOUT_FILENO);
	}
	else
	{
		my_close(&data->pipefd[i - 1][1]);
		my_close(&data->pipefd[i][0]);
		ft_dup2(data->pipefd[i - 1][0], STDIN_FILENO);
		ft_dup2(data->pipefd[i][1], STDOUT_FILENO);
	}
	ft_close_all(data);
}

void	ft_child(t_data *data, int i, char **env)
{
	set_child(data, i);
	execve(data->path_cmds[i], data->split_cmds[i], env);
	if (data->path_cmds[i])
	{
		if (!access(data->path_cmds[i], X_OK))
		{
			my_perror("pipex: ", data->split_cmds[i][0]);
			my_perror(": not an executable file\n", NULL);
			ft_free2(data);
			exit(1);
		}
		my_perror("pipex: ", data->split_cmds[i][0]);
		my_perror(": command is found but is not executable\n", NULL);
		ft_free2(data); 
		exit(126);
	}
	else
	{
		my_perror("pipex: ", data->split_cmds[i][0]);
		my_perror(": command not found\n", NULL);
		ft_free2(data);
	}
	exit(127);
}

void	ft_parent(t_data *data, int i)
{
	if (i == 0)
	{
		my_close(&data->fdin);
		if (data->nbr_cmd == 1)
			my_close(&data->fdout);
		else
			my_close(&data->pipefd[i][1]);
	}
	else if (i == data->nbr_cmd - 1)
	{
		my_close(&data->pipefd[i - 1][0]);
		my_close(&data->fdout);
	}
	else
	{
		my_close(&data->pipefd[i - 1][0]);
		my_close(&data->pipefd[i][1]);
	}
}

void	ft_close_all(t_data *data)
{
	int	i;

	i = 0;
	my_close(&data->fdin);
	my_close(&data->fdout);
	while (i < data->nbr_cmd - 1)
	{
		my_close(&data->pipefd[i][0]);
		my_close(&data->pipefd[i][1]);
		i++;
	}
}
