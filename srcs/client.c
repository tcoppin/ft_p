/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 18:37:45 by tcoppin           #+#    #+#             */
/*   Updated: 2015/05/08 18:30:25 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int		create_client(char *addr, int port)
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
	s_in.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
	{
		write(1, "Error connect\n", 14);
		exit(2);
	}
	return (sock);
}

int		ft_put_prompt()
{
	ft_putstr("\033[32m$> \033[00m");
	return (1);
}

void	read_server(int sock)
{
	int		r;
	char	buf[2048];
	char	*rtn;

	if ((r = recv(sock, buf, 2047, 0)) > 0)
	{
		buf[r] = '\0';
		rtn = ft_strtrim(buf);
		ft_putendl(rtn);
		free(rtn);
	}
}

int		main(int ac, char **av)
{
	int		port;
	int		sock;
	char	*line;

	if (ac != 3)
		ft_usage_cl(av[0]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	while (ft_put_prompt())
	{
		if (get_next_line(0, &line) > 0)
		{
			send(sock, (const void *)line, sizeof(line), MSG_DONTROUTE);
			read_server(sock);
			free(line);
		}
	}
	close(sock);
	return (0);
}
