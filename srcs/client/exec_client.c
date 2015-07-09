/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 16:03:32 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/29 18:44:39 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		exec_put_cl(t_client *all_c, char *cmd_all, char **cmd_array)
{
	int			fd;
	int			rd;
	int			r;
	char		tmp[2048];
	struct stat	buf;

	write_server(all_c, cmd_all);
	fd = open(cmd_array[1], O_RDONLY);
	if (fd >= 0 && fstat(fd, &buf) == 0)
	{
		r = recv(all_c->sock, all_c->buf, 2047, 0);
		all_c->buf[r] = '\0';
		ft_putstr(all_c->buf);
		if (ft_strequ(all_c->buf, "Ok\n"))
		{
			write_server(all_c, ft_itoa(buf.st_size));
			while ((rd = read(fd, tmp, 2047)) > 0)
			{
				tmp[rd] = '\0';
				// write(0, tmp, rd);
				write(all_c->sock, tmp, rd);
			}
		}
	}
	close(fd);
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
