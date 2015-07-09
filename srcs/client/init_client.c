/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 19:32:19 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/04 12:12:56 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	ft_init_client(t_client *all_c, char **av)
{
	all_c->port = ft_atoi(av[2]);
	all_c->addr = av[1];
	all_c->quit = 0;
}

void	init_dir(t_client *all_c)
{
	char	*tmp;
	int		r;

	tmp = NULL;
	write_server(all_c, "whoami init");
	r = read_server(all_c);
	all_c->buf[r - 1] = '\0';
	all_c->root = ft_strjoin("client_", all_c->buf);
	mkdir(all_c->root, 0777);
	chdir(all_c->root);
	all_c->src_dir = getcwd(tmp, 1024);
	all_c->cur_dir = ft_strdup(all_c->root);
}

int		create_client(char *addr, t_client *all_c)
{
	struct protoent		*proto;
	struct sockaddr_in	s_in;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	all_c->sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(all_c->port);
	s_in.sin_addr.s_addr = inet_addr(addr);
	if (connect(all_c->sock, (SOCKADDR *)&s_in, sizeof(s_in)) == -1)
	{
		ft_putendl("\033[1;31m-- Connect to the server ERROR --\033[00m");
		exit(2);
	}
	ft_putendl("\033[1;32m-- Connect to the server SUCCESS --\033[00m");
	init_dir(all_c);
	return (1);
}
