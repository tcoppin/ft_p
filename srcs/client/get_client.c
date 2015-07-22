/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/22 17:27:14 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/22 17:45:57 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	get_file(int fd, t_client *all_c, int size[3])
{
	char	tmp[2048];
	char	*save;

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

int		exec_get_cl(t_client *all_c, char *cmd_all, char **cmd_array)
{
	int		fd;
	int		size[3];

	write_server(all_c, cmd_all);
	size[0] = recv(all_c->sock, all_c->buf, 2047, 0);
	all_c->buf[size[0]] = '\0';
	if (ft_strequ(all_c->buf, "Ok\n"))
	{
		if ((fd = open(cmd_array[1], O_WRONLY | O_CREAT, 0644)) >= 0)
			get_file(fd, all_c, size);
		close(fd);
	}
	else
	{
		ft_putstr(all_c->buf);
		return (-1);
	}
	return (1);
}
