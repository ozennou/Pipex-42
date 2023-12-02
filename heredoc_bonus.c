/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:14:30 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 12:33:23 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	read_heredoc(char *limiter, t_data *data)
{
	int		fd[2];
	char	*buffer;
	char	*tmp;
	int		i;

	tmp = ft_strjoin(limiter, "\n");
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		i = 0;
		while (++i < data->nbr_cmd)
			ft_putstr("pipe ");
		ft_putstr("heredoc> ");
		buffer = get_next_line(0);
		if (!buffer)
			return (free(tmp), close(fd[0]), close(fd[1]), fd[0]);
		if (!ft_strncmp(buffer, tmp, ft_strlen(tmp) + 1))
			return (free(buffer), free(tmp), close(fd[1]), fd[0]);
		write(fd[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	return (0);
}

void	ft_here_doc(int ac, char **av, char **env, t_data *data)
{
	if (ac < 5)
	{
		my_perror("Usage: ./pipex here_doc LIMITER ", NULL);
		my_perror("cmd1 cmd2 cmd3 ... cmdn file\n", NULL);
		exit(1);
	}
	if (set_data(av, env, data))
		exit(1);
}

void	ft_one_cmd(t_data *data, char **env)
{
	ft_dup2(data->fdin, STDIN_FILENO);
	ft_dup2(data->fdout, STDOUT_FILENO);
	close(data->fdin);
	close(data->fdout);
	execve(data->path_cmds[0], data->split_cmds[0], env);
	if (data->path_cmds[0])
	{
		if (!access(data->path_cmds[0], X_OK))
		{
			my_perror("pipex: ", data->split_cmds[0][0]);
			my_perror(": not an executable file\n", NULL);
			exit(1); 
		}
		my_perror("pipex: ", data->split_cmds[0][0]);
		my_perror(": command is found but is not executable\n", NULL);
		ft_free2(data);
		exit(126);
	}
	else
	{
		my_perror("pipex: ", data->split_cmds[0][0]);
		my_perror(": command not found\n", NULL);
		ft_free2(data);
	}
	exit(127);
}

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

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}
