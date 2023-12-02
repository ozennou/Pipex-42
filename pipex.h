/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:16:36 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 18:25:15 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		fdin;
	int		fdout;
	int		pipefd[2];
	char	*path_cmd1;
	char	*path_cmd2;
	char	**split_cmd1;
	char	**split_cmd2;
	char	**paths;
}	t_data;

char	*ft_strjoin(char const *a, char const *b);
char	**ft_split(char const *s, char c);
char	**my_split(char const *s);
size_t	ft_strlcpy(char *d, const char *s, unsigned int n);
void	ft_dup2(int fd1, int fd2);
int		checkerror(char **av, int ac);
void	ft_open(char **av, int *fdin, int *fdout, t_data *data);
void	ft_error(t_data *data);
char	*get_cmd(char *cmd, char **path);
int		set_data(char **av, char **env, t_data *data);
void	ft_free2(t_data *data);
char	*ft_strchr(const char *s, int c);
void	first_cmd(t_data *data, char **env);
void	ft_end(t_data *data, pid_t pid1, char **env);
char	*ft_strdup(const char *s);
void	set_path(char **path);
int		ft_strncmp(const char *a, const char *b, size_t n);
void	my_perror(char *s1, char *s2);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *d, const void *s, size_t n);

#endif