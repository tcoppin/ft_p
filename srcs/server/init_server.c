/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 14:54:23 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/23 15:48:40 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	ft_init_serv(t_serv *all_s, char **av)
{
	all_s->port = ft_atoi(av[1]);
}

int		create_server(t_serv *all_s)
{
	struct protoent		*proto;
	struct sockaddr_in	s_in;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	all_s->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(all_s->port);
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(all_s->sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
	{
		write(1, "Error bind\n", 11);
		exit(2);
	}
	listen(all_s->sock, 47);
	all_s->dir = ft_strdup("d_server");
	mkdir(all_s->dir, 0777);
	all_s->fd = open("ft_p.log", O_WRONLY | O_CREAT, 0644);
	lseek(all_s->fd, 0, SEEK_END);
	put_in_log("/!\\ Server start /!\\\n", all_s);
	ft_putendl("\033[1;32m-- Hello I am a ft_p server --\033[00m");
	return (1);
}

void	init_client(t_cus *cus, t_serv *all_s)
{
	char	*tmp;

	tmp = NULL;
	cus->cur_dir = ft_strdup(all_s->dir);
	chdir(cus->cur_dir);
	all_s->root = getcwd(tmp, 1024);
	cus->old_dir = NULL;
}
