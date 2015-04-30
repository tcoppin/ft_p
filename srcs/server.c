/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 13:16:48 by tcoppin           #+#    #+#             */
/*   Updated: 2015/04/30 20:13:23 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	s_in;
	char				*dir;

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
	dir = ft_strjoin("server_", ft_itoa(sock));
	mkdir(dir, 0777);
	return (sock);
}

void	exec_bin(char **cmd, int cs)
{
	pid_t	pid;

	cmd[0] = ft_strdup(ft_strjoin("/bin/", cmd[0]));
	if (open(cmd[0], O_RDONLY) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(cs, 0);
			dup2(cs, 1);
			dup2(cs, 2);
			close(cs);
			execv(cmd[0], cmd);
		}
	}
	else
		ft_putstr_fd("Command not found.\n", cs);
}

void	connect_cus(int cs, int sock)
{
	int		r;
	char	buf[2048];
	pid_t	pid;
	char	*dir;
	char	*rtn;
	char	**cmd;

	cmd = NULL;
	pid = fork();
	dir = ft_strjoin("client_", ft_itoa(cs));
	mkdir(dir, 0777);
	if (pid == 0)
	{
		chdir(ft_strjoin("server_", ft_itoa(sock)));
		while ((r = read(cs, buf, 2047)) > 0)
		{
			buf[r] = '\0';
			rtn = ft_strtrim(buf);
			cmd = ft_strsplit(rtn, 32);
			exec_bin(cmd, cs);
		}
		close(cs);
		exit(0);
	}
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
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&c_sin, &cslen);
		connect_cus(cs, sock);
	}
	close(sock);
	return (0);
}
