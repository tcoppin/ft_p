/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 17:19:25 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/22 17:56:13 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	ft_send_file(t_cus *cus, int fd, struct stat buf)
{
	char		tmp[2048];
	int			rd;
	int			r;

	if (ft_strequ(cus->buf, "Ok\n"))
	{
		ft_bzero(tmp, 2048);
		write_client(cus, ft_itoa(buf.st_size));
		r = recv(cus->cs, cus->buf, 2047, 0);
		cus->buf[r] = '\0';
		if (ft_strequ(cus->buf, "Ok\n"))
		{
			while ((rd = read(fd, tmp, 2047)) > 0)
			{
				tmp[rd] = '\0';
				write(cus->cs, tmp, rd);
				ft_bzero(tmp, 2048);
			}
		}
	}
}

void	finish_get(int i[2], t_cus *cus, char *save)
{
	i[1] = recv(cus->cs, cus->buf, 2047, 0);
	cus->buf[i[1]] = '\0';
	if (ft_strequ(cus->buf, "Ok\n"))
		;
	ft_strclr(cus->buf);
	ft_strcat(cus->buf, save);
	free(save);
	close(i[0]);
}

int		exec_get(t_cus *cus, char **cmd_array)
{
	int			i[2];
	DIR			*pdir;
	char		*save;
	struct stat	buf;

	if (!(pdir = opendir(cmd_array[1])) &&
		(i[0] = open(cmd_array[1], O_RDONLY)) >= 0)
	{
		write_client(cus, "Ok");
		if ((save = ft_strdup(cus->buf)) && fstat(i[0], &buf) == 0)
		{
			i[1] = recv(cus->cs, cus->buf, 2047, 0);
			cus->buf[i[1]] = '\0';
			ft_send_file(cus, i[0], buf);
		}
		finish_get(i, cus, save);
	}
	else
	{
		if (pdir)
			closedir(pdir);
		write_client(cus, "\033[1;33mget: Can't open the file.\033[00m");
		return (-1);
	}
	return (1);
}
