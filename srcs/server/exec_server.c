/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 12:01:40 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/29 14:26:45 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		exec_put(t_cus *cus, char **cmd_array)
{
	int		rd;
	int		tot;
	int		size;
	char	*save;
	char	tmp[2048];
	
	ft_putendl(cmd_array[1]);
	save = ft_strdup(cus->buf);
	write_client(cus, "Ok");
	read_client(cus);
	size = ft_atoi(cus->buf);
	tot = 0;
	while (tot < size)
	{
		rd = recv(cus->cs, tmp, 2047, 0);
		tot += rd;
		write(0, tmp, rd);
	}
	ft_strclr(cus->buf);
	ft_strcat(cus->buf, save);
	free(save);
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
