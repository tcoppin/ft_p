/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 19:24:30 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/23 12:53:41 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		ft_put_prompt(t_client *all_c)
{
	ft_putstr("\033[32m");
	ft_putstr(all_c->root);
	ft_putstr("@");
	ft_putstr(all_c->addr);
	ft_putstr("\033[00m $> \033[34;01m");
	if (ft_strequ(all_c->cur_dir, all_c->root))
		ft_putstr("/");
	else
		ft_putstr(ft_strchr(all_c->cur_dir, '/'));
	ft_putstr(" : ");
	ft_putstr("\033[00m");
	return (1);
}

void	brain_client(t_client *all_c)
{
	char	**cmd_all;
	char	**cmd_array;
	int		i;

	i = 0;
	if (all_c->line)
	{
		cmd_all = ft_strsplit(all_c->line, ';');
		while (cmd_all[i])
		{
			cmd_all[i] = ft_strreplace(cmd_all[i], 9, 32);
			cmd_array = ft_strsplit(cmd_all[i], ' ');
			if (cmd_array[0])
				check_cmd_cl(cmd_array, all_c, cmd_all[i]);
			i++;
		}
	}
}

int		main(int ac, char **av)
{
	t_client		all_c;
	struct hostent	*hp;
	struct in_addr	**addr_list;
	
	if (ac != 3)
		ft_error_client(USG, av[0]);
	if ((hp = gethostbyname(av[1])) == NULL)
	{
		ft_putendl("\033[1;31m-- Connect to the server ERROR --\033[00m");
		exit(2);
	}
	addr_list = (struct in_addr **)hp->h_addr_list;
	ft_init_client(&all_c, av, inet_ntoa(*addr_list[0]));
	create_client(inet_ntoa(*addr_list[0]), &all_c);
	while (all_c.quit == 0 && ft_put_prompt(&all_c))
	{
		if (get_next_line(0, &(all_c).line) > 0)
		{
			brain_client(&all_c);
			free(all_c.line);
		}
	}
	close(all_c.sock);
	return (0);
}
