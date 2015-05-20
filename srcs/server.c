/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 18:37:37 by tcoppin           #+#    #+#             */
/*   Updated: 2015/05/08 18:33:45 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	exec_bin(char **cmd, int cs)
{
	pid_t			pid;
	int				status;
	struct rusage	rusage;

	cmd[0] = ft_strjoin("/bin/", cmd[0]);
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
		else
			wait4(pid, &status, 0, &rusage);
	}
	else
		ft_putstr_fd("Command not found.\n", cs);
}

int		read_client(int cs)
{
	int		r;
	char	buf[2048];
	char	*rtn;
	char	**cmd;

	cmd = NULL;
	if ((r = recv(cs, buf, 2047, 0)) > 0)
	{
		buf[r] = '\0';
		rtn = ft_strtrim(buf);
		cmd = ft_strsplit(rtn, 32);
		free(rtn);
		if (ft_strequ(cmd[0], "quit"))
		{
			free(cmd);
			return (0);
		}
		exec_bin(cmd, cs);
		free(cmd);
	}
	return (1);
}

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

void		connect_cus(int cs)
{
	pid_t	pid;
	char	*dir;

	pid = fork();
	if (pid == 0)
	{
		dir = ft_strjoin("client_", ft_itoa(cs));
		mkdir(dir, 0777);
		// chdir(dir);
		while (read_client(cs) > 0)
			;
		close(cs);
		free(dir);
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
	port = ft_atoi(av[1]);
	sock = create_server(port);
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&c_sin, &cslen);
		connect_cus(cs);
	}
	close(sock);
	return (0);
}
