/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 15:52:37 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/21 14:35:12 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	return_serv(t_client *all_c)
{
	int		r;
	int		br;

	br = 0;
	while ((r = read_server(all_c)) > 0)
	{
		if (all_c->buf[r - 1] == '\0')
			br = 1;
		ft_putstr(all_c->buf);
		if (br == 1)
			break ;
	}
}

int		is_bin(char **cmd_array)
{
	int		i;

	i = 0;
	if (ft_strequ(cmd_array[0], "lls"))
		i = exec_l_cmd(cmd_array, "/bin/ls");
	else if (ft_strequ(cmd_array[0], "lmkdir"))
		i = exec_l_cmd(cmd_array, "/bin/mkdir");
	else if (ft_strequ(cmd_array[0], "lrm"))
		i = exec_l_cmd(cmd_array, "/bin/rm");
	else if (ft_strequ(cmd_array[0], "clear"))
		i = exec_l_cmd(cmd_array, "/usr/bin/clear");
	return (i);
}

int		is_client(char **cmd_array, t_client *all_c, char *cmd_all)
{
	int		i;

	i = 0;
	if (ft_strequ(cmd_array[0], "lpwd"))
		i = exec_l_pwd(all_c, cmd_array);
	else if (ft_strequ(cmd_array[0], "lcd"))
		i = exec_l_cd(all_c, cmd_array);
	else if (is_bin(cmd_array))
		i = 1;
	// else if (ft_strequ(cmd_array[0], "get"))
	// 	i = exec_get_cl(all_c, cmd_all);
	else if (ft_strequ(cmd_array[0], "put"))
	{
		i = exec_put_cl(all_c, cmd_all, cmd_array);
		if (i > 0)
			return_serv(all_c);
	}
	else if (ft_strequ(cmd_array[0], "quit"))
		i = exec_l_quit(all_c, cmd_all);
	return (i);
}

void	check_cmd_cl(char **cmd_array, t_client *all_c, char *cmd_all)
{
	if (is_client(cmd_array, all_c, cmd_all))
		;
	else
	{
		write_server(all_c, cmd_all);
		return_serv(all_c);
	}
}
