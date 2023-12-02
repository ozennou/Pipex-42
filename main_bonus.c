/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:19:47 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 12:36:37 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check1(char *s)
{
	if (access(s, F_OK))
	{
		my_perror("pipex: ", s);
		my_perror(" : No such file or directory\n", NULL);
		return (1);
	}
	return (0);
}

void	general_check(int ac, char **av, char **env, t_data *data)
{
	int	i;

	i = 0;
	data->here_doc = 0;
	data->nbr_cmd = ac - 3;
	if (ac < 4)
	{
		my_perror("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", NULL);
		exit(1);
	}
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		data->nbr_cmd = ac - 4;
		data->here_doc = 1;
		data->limiter = av[2];
		ft_here_doc(ac, av, env, data);
		return ;
	}
	if (!check1(av[1]))
		checkerror(av, ac);
	if (set_data(av, env, data))
		exit(1);
}

void	ft_pipe(t_data *data)
{
	int	i;

	i = 0;
	data->pid = malloc(sizeof (pid_t) * (data->nbr_cmd));
	if (!data->pid)
		ft_error(data);
	while (i < data->nbr_cmd - 1)
	{
		data->pipefd[i] = malloc(sizeof (int) * 2);
		if (!data->pipefd[i])
			ft_error(data);
		if (pipe(data->pipefd[i]) == -1)
			ft_error(data);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		i;

	general_check(ac, av, env, &data);
	ft_open(ac, av, &data);
	ft_pipe(&data);
	if (data.nbr_cmd == 1)
		return (ft_one_cmd(&data, env), 0);
	i = 0;
	while (i < data.nbr_cmd)
	{
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			ft_error(&data);
		if (data.pid[i] == 0)
			ft_child(&data, i, env);
		else
			ft_parent(&data, i);
		i++;
	}
	while (i--)
		waitpid(data.pid[i], NULL, 0);
	ft_free2(&data);
	return (0);
}
