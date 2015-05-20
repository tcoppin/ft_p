/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 13:16:54 by tcoppin           #+#    #+#             */
/*   Updated: 2015/05/01 16:05:06 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

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

int		ft_put_prompt(void)
{
	ft_putstr("\033[32m$> \033[00m");
	return (1);
}

int		main(int ac, char **av)
{
	int		port;
	int		sock;
	char	*line;
	char	buf[4096];
	int		r;

	if (ac != 3)
		ft_usage_cl(av[0]);
	if (!check_port_nb(av[2], av[0]))
		return (0);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	while (ft_put_prompt())
	{
		if (get_next_line(0, &line) > 0)
		{
			send(sock, (const void *)line, sizeof(line), MSG_DONTROUTE);
			if (ft_strequ(line, "quit"))
			{
				while ((r = recv(sock, buf, 4095, MSG_WAITALL)) > 0)
					continue ;
				break ;
			}
			while ((r = recv(sock, buf, 4095, 0)) > 0)
			{
				buf[r] = '\0';
				ft_putstr(buf);
				if (buf[r - 1] == '\n')
					break ;
			}
			free(line);
		}
	}
	close(sock);
	return (0);
}