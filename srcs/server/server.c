/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 17:40:22 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/22 22:46:22 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	server_app(t_cus *cus, t_serv *all_s)
{
	char	*cmd_all;
	char	**cmd_array;
	int		i;

	i = 0;
	if (cus->buf)
	{
		cmd_all = ft_strreplace(cus->buf, 9, 32);
		cmd_array = ft_strsplit(cmd_all, ' ');
		if (cmd_array[0])
			check_cmd(cmd_array, cus, all_s);
		i++;
	}
}

void	ft_client_msg(t_cus *cus, int i)
{
	ft_putstr("\033[1;34m");
	ft_putstr("-- Client \"");
	ft_putnbr(cus->cs);
	if (i == 1)
		ft_putstr("\" is now connect ");
	else if (i == 2)
		ft_putstr("\" is now disconnect ");
	ft_putendl(" --\033[00m");
}

void	connect_cus(t_serv *all_s)
{
	t_cus	cus;
	int		r;

	cus.cs = all_s->cs;
	signal(SIGCHLD, SIG_IGN);
	cus.pid = fork();
	if (cus.pid == 0)
	{
		init_client(&cus, all_s);
		ft_client_msg(&cus, 1);
		while ((r = read_client(&cus)) > 0)
		{
			if (ft_strnequ(cus.buf, "quit", 4))
			{
				ft_client_msg(&cus, 2);
				break ;
			}
			server_app(&cus, all_s);
		}
	}
	if (cus.pid <= 0)
	{
		close(all_s->cs);
		exit(cus.pid);
	}
}

int		main(int ac, char **av)
{
	t_serv				all_s;
	unsigned int		cslen;
	struct sockaddr_in	c_sin;

	if (ac != 2)
		ft_error_server(USG, av[0]);
	ft_init_serv(&all_s, av);
	create_server(&all_s);
	while (42)
	{
		all_s.cs = accept(all_s.sock, (struct sockaddr *)&c_sin, &cslen);
		if (all_s.cs > 0)
			connect_cus(&all_s);
		else
			ft_error_server(OTH, "A client want to connect and accept fail.");
	}
	close (all_s.sock);
	return (0);
}
