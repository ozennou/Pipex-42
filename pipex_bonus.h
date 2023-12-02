/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:16:36 by mozennou          #+#    #+#             */
/*   Updated: 2023/12/02 10:29:07 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		**pipefd;
	int		nbr_cmd;
	int		here_doc;
	char	*limiter;
	char	**path_cmds;
	char	***split_cmds;
	char	**paths;
	pid_t	*pid;
}	t_data;

char	*ft_strjoin(char const *a, char const *b);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	**my_split(char const *s);
size_t	ft_strlcpy(char *d, const char *s, unsigned int n);
void	ft_dup2(int fd1, int fd2);
int		checkerror(char **av, int ac);
void	ft_open(int ac, char **av, t_data *data);
void	ft_error(t_data *data);
char	*get_cmd(char *cmd, char **path);
char	*get_path(char **env);
void	ft_close(t_data *data);
int		set_data(char **av, char **env, t_data *data);
void	ft_free2(t_data *data);
char	*ft_strchr(const char *s, int c);
void	ft_child(t_data *data, int i, char **env);
void	ft_parent(t_data *data, int i);
int		ft_strncmp(const char *a, const char *b, size_t n);
void	ft_here_doc(int ac, char **av, char **env, t_data *data);
char	*ft_strdup(const char *s);
int		read_heredoc(char *limiter, t_data *data);
void	set_path(char **path);
void	my_close(int *fd);
void	ft_one_cmd(t_data *data, char **env);
void	my_perror(char *s1, char *s2);
void	ft_close_all(t_data *data);
size_t	ft_strlen(const char *s);
void	ft_putstr(char *s);
void	*ft_memcpy(void *d, const void *s, size_t n);

#endif