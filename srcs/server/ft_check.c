/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 18:47:02 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/22 16:56:53 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		is_builtin(char **cmd_array, t_cus *cus, t_serv *all_s)
{
	int		i;

	i = 0;
	if (ft_strequ(cmd_array[0], "pwd"))
		i = exec_pwd(cus, cmd_array, all_s);
	else if (ft_strequ(cmd_array[0], "cd"))
		i = exec_cd(cus, cmd_array, all_s);
	else if (ft_strequ(cmd_array[0], "get"))
		i = exec_get(cus, cmd_array);
	else if (ft_strequ(cmd_array[0], "put"))
		i = exec_put(cus, cmd_array);
	return (i);
}

int		is_binary(char **cmd_array, t_cus *cus)
{
	int		i;

	i = 0;
	if (ft_strequ(cmd_array[0], "ls"))
		i = exec_cmd(cus, cmd_array, "/bin/ls");
	else if (ft_strequ(cmd_array[0], "mkdir"))
		i = exec_cmd(cus, cmd_array, "/bin/mkdir");
	else if (ft_strequ(cmd_array[0], "rm"))
		i = exec_cmd(cus, cmd_array, "/bin/rm");
	return (i);
}

void	check_cmd(char **cmd_array, t_cus *cus, t_serv *all_s)
{
	int		i;

	i = 0;
	if (ft_strequ(cmd_array[0], "whoami"))
	{
		write_client(cus, ft_itoa(cus->cs));
		if (ft_strequ(cmd_array[1], "init"))
			return ;
		i = 1;
	}
	else if (is_builtin(cmd_array, cus, all_s))
		i = 1;
	else if (is_binary(cmd_array, cus))
		i = 1;
	else
		write_client(cus, "Command not found.");
	if (i > 0)
		write_client(cus,
		"\033[1;32m-- Server return a SUCCESS --\n\033[00m\0");
	else
		write_client(cus, "\033[1;31m-- Server return an ERROR --\n\033[00m\0");
	ft_put_hist(cus, i);
	send(cus->cs, "\0", 1, 0);
}
