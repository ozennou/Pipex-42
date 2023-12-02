/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:19:47 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 15:19:14 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check1(char *s)
{
	if (access(s, F_OK))
	{
		my_perror("pipex: ", s);
		my_perror(": No such file or directory\n", NULL);
		return (1);
	}
	return (0);
}

void	general_check(int ac, char **av, char **env, t_data *data)
{
	if (ac != 5)
	{
		my_perror("Usage: ./pipex file1 cmd1 cmd2 file2\n", NULL);
		exit(1);
	}
	if (!check1(av[1]))
		checkerror(av, ac);
	if (set_data(av, env, data))
		exit(1);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	pid_t	pid0;
	pid_t	pid1;

	pid1 = 0;
	general_check(ac, av, env, &data);
	ft_open(av, &data.fdin, &data.fdout, &data);
	if (pipe(data.pipefd) == -1)
		ft_error(&data);
	pid0 = fork();
	if (pid0 == -1)
		ft_error(&data);
	if (pid0 == 0)
		first_cmd(&data, env);
	else
	{
		ft_end(&data, pid1, env);
		wait(NULL);
		wait(NULL);
	}
	close(data.fdin);
	close(data.fdout);
	ft_free2(&data);
	return (0);
}
