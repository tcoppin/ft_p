/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 13:16:48 by tcoppin           #+#    #+#             */
/*   Updated: 2015/04/29 03:27:05 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

//check si port == number
//check si port est superieur à 1024

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	s_in;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
	{
		write(1, "Error bind\n", 11);
		exit(2);
	}
	listen(sock, 47);
	return (sock);
}

void	connect_cus(int cs)
{
	int					r;
	char				buf[2048];

	while ((r = read(cs, buf, 2047)) > 0)
	{
		buf[r] = '\0';
		write(1, buf, ft_strlen(buf));
	}
	close(cs);
}

int		main(int ac, char **av)
{
	int					port;
	int					sock;
	unsigned int		cslen;
	struct sockaddr_in	c_sin;
	int					cs;

	if (ac != 2)
		ft_usage(av[0]);
	if (!check_port_nb(av[1], av[0]))
		return (0);
	port = ft_atoi(av[1]);
	if (!check_port_range(port, av[0]))
		return (0);
	sock = create_server(port);
	cs = accept(sock, (struct sockaddr *)&c_sin, &cslen);
	connect_cus(cs);
	close(sock);
	return (0);
}
