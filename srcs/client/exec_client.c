/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 16:03:32 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/22 16:49:53 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		exec_get_cl(t_client *all_c, char *cmd_all, char **cmd_array)
{
	int		fd;
	int		size[3];
	char	*save;
	char	tmp[2048];

	write_server(all_c, cmd_all);
	size[0] = recv(all_c->sock, all_c->buf, 2047, 0);
	all_c->buf[size[0]] = '\0';
	if (ft_strequ(all_c->buf, "Ok\n"))
	{
		if ((fd = open(cmd_array[1], O_WRONLY | O_CREAT, 0644)) >= 0)
		{
			save = ft_strdup(all_c->buf);
			write_server(all_c, "Ok");
			read_server(all_c);
			size[2] = ft_atoi(all_c->buf);
			write_server(all_c, "Ok");
			size[1] = 0;
			while (size[1] < size[2])
			{
				size[0] = recv(all_c->sock, tmp, 2047, 0);
				size[1] += size[0];
				write(fd, tmp, size[0]);
			}
			write_server(all_c, "Ok");
			ft_strclr(all_c->buf);
			ft_strcat(all_c->buf, save);
			free(save);
		}
		close(fd);
	}
	return (1);
}

void	ft_send_file(t_client *all_c, int fd, struct stat buf)
{
	char		tmp[2048];
	int			rd;
	int			r;

	ft_bzero(tmp, 2048);
	write_server(all_c, ft_itoa(buf.st_size));
	r = recv(all_c->sock, all_c->buf, 2047, 0);
	all_c->buf[r] = '\0';
	if (ft_strequ(all_c->buf, "Ok\n"))
	{
		while ((rd = read(fd, tmp, 2047)) > 0)
		{
			tmp[rd] = '\0';
			write(all_c->sock, tmp, rd);
			ft_bzero(tmp, 2048);
		}
	}
}

int		exec_put_cl(t_client *all_c, char *cmd_all, char **cmd_array)
{
	int			i[2];
	DIR			*pdir;
	struct stat	buf;

	if (!(pdir = opendir(cmd_array[1])) &&
		(i[0] = open(cmd_array[1], O_RDONLY)) >= 0)
	{
		write_server(all_c, cmd_all);
		if (fstat(i[0], &buf) == 0)
		{
			i[1] = recv(all_c->sock, all_c->buf, 2047, 0);
			all_c->buf[i[1]] = '\0';
			if (ft_strequ(all_c->buf, "Ok\n"))
				ft_send_file(all_c, i[0], buf);
		}
		close(i[0]);
	}
	else
	{
		if (pdir)
			closedir(pdir);
		ft_putendl("\033[1;33mput: Can't open the file.\033[00m");
		return (-1);
	}
	return (1);
}

int		exec_l_cmd(char **cmd_array, char *bin)
{
	pid_t			pid;
	int				status;
	struct rusage	m_rusage;

	pid = fork();
	if (pid < 0)
	{
		ft_putendl("\033[1;33mError when exec the command.\033[00m");
		return (0);
	}
	if (pid == 0)
	{
		if (execv(bin, cmd_array) < 0)
		{
			ft_putendl("\033[1;33mError when exec the command.\033[00m");
			return (0);
		}
	}
	else
		wait4(pid, &status, 0, &m_rusage);
	return (1);
}

int		exec_l_pwd(t_client *all_c, char **cmd_array)
{
	if (cmd_array[1])
	{
		ft_putendl("\033[1;33mpwd: Too many arguments.\033[00m");
		return (0);
	}
	else
	{
		if (ft_strequ(all_c->cur_dir, all_c->root))
			ft_putendl("/");
		else
			ft_putendl(ft_strchr(all_c->cur_dir, '/'));
	}
	return (1);
}

int		exec_l_quit(t_client *all_c, char *cmd_all)
{
	write_server(all_c, cmd_all);
	all_c->quit = 1;
	return (1);
}
