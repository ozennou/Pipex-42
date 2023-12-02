/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:46:58 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 09:46:55 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_perror(char *s1, char *s2)
{
	if (s1)
	{
		while (*s1)
			write(2, s1++, 1);
	}
	if (s2)
	{
		while (*s2)
			write(2, s2++, 1);
	}
}

void	first_cmd(t_data *data, char **env)
{
	close(data->pipefd[0]);
	close(data->fdout);
	ft_dup2(data->fdin, STDIN_FILENO);
	ft_dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->fdin);
	close(data->pipefd[1]);
	execve(data->path_cmd1, data->split_cmd1, env);
	if (data->path_cmd1)
	{
		if (!access(data->path_cmd1, X_OK))
		{
			my_perror("pipex: ", data->split_cmd1[0]);
			my_perror(": not an executable file\n", NULL);
			return (ft_free2(data), exit(1));
		}
		my_perror("pipex: ", data->split_cmd1[0]);
		my_perror(": command is found but is not executable\n", NULL);
		return (ft_free2(data), exit(126));
	}
	else
	{
		my_perror("pipex: ", data->split_cmd1[0]);
		my_perror(": command not found\n", NULL);
		return (ft_free2(data), exit(127));
	}
}

void	second_cmd(t_data *data, char **env)
{
	close(data->pipefd[1]);
	close(data->fdin);
	ft_dup2(data->fdout, STDOUT_FILENO);
	ft_dup2(data->pipefd[0], STDIN_FILENO);
	close(data->fdout);
	close(data->pipefd[0]);
	execve(data->path_cmd2, data->split_cmd2, env);
	if (data->path_cmd2)
	{
		if (!access(data->path_cmd2, X_OK))
		{
			my_perror("pipex: ", data->split_cmd2[0]);
			my_perror(": not an executable file\n", NULL);
			return (ft_free2(data), exit(1));
		}
		my_perror("pipex: ", data->split_cmd2[0]);
		my_perror(": command is found but is not executable\n", NULL);
		return (ft_free2(data), exit(126));
	}
	else
	{
		my_perror("pipex: ", data->split_cmd2[0]);
		my_perror(": command not found\n", NULL);
		return (ft_free2(data), exit(127));
	}
}

void	ft_end(t_data *data, pid_t pid1, char **env)
{
	pid1 = fork();
	if (pid1 == -1)
		ft_error(data);
	if (pid1 == 0)
		second_cmd(data, env);
	else
	{
		close(data->fdin);
		close(data->fdout);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
}

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen((char *)s);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	while (++i < len)
		res[i] = s[i];
	res[i] = '\0';
	return (res);
}
