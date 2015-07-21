/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 12:01:40 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/21 14:34:43 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		exec_put(t_cus *cus, char **cmd_array)
{
	int		fd;
	int		size[3];
	char	*save;
	char	tmp[2048];

	if ((fd = open(cmd_array[1], O_WRONLY | O_CREAT, 0644)) >= 0)
	{
		save = ft_strdup(cus->buf);
		write_client(cus, "Ok");
		read_client(cus);
		size[2] = ft_atoi(cus->buf);
		write_client(cus, "Ok");
		size[1] = 0;
		while (size[1] < size[2])
		{
			size[0] = recv(cus->cs, tmp, 2047, 0);
			size[1] += size[0];
			write(fd, tmp, size[0]);
		}
		ft_strclr(cus->buf);
		ft_strcat(cus->buf, save);
		free(save);
	}
	close(fd);
	return (1);
}

int		exec_cmd(t_cus *cus, char **cmd_array, char *bin)
{
	pid_t			pid;
	int				status;
	struct rusage	m_rusage;

	pid = fork();
	if (pid < 0)
	{
		write_client(cus, "\033[1;33mError when exec the command.\033[00m");
		return (0);
	}
	if (pid == 0)
	{
		dup2(cus->cs, 0);
		dup2(cus->cs, 1);
		dup2(cus->cs, 2);
		close(cus->cs);
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

int		exec_pwd(t_cus *cus, char **cmd_array, t_serv *all_s)
{
	if (cmd_array[1])
	{
		write_client(cus, "\033[1;33mpwd: Too many arguments.\033[00m");
		return (0);
	}
	else
	{
		if (ft_strequ(cus->cur_dir, all_s->dir))
			write_client(cus, "/");
		else
			write_client(cus, ft_strchr(cus->cur_dir, '/'));
	}
	return (1);
}
