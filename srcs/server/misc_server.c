/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 17:42:39 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/02 19:59:22 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	ft_error_server(int i, char *str)
{
	if (i == USG)
	{
		ft_putstr_fd("\033[1;33mUsage : ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" <port>\033[00m", 2);
		exit(-1);
	}
	else if (i == OTH)
	{
		ft_putstr_fd("\033[1;33m", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("\033[00m", 2);
	}
}

void	ft_put_hist(t_cus *cus, int i)
{
	if (i > 0)
		ft_putstr("\033[1;32m");
	else
		ft_putstr("\033[1;31m");
	ft_putstr("-- Execute \"");
	ft_putstr(cus->buf);
	ft_putstr("\" by client ");
	ft_putnbr(cus->cs);
	if (i > 0)
		ft_putendl(" and it's a SUCCESS --\033[00m");
	else
		ft_putendl(" and it's an ERROR --\033[00m");
}

char	*ft_leave_tab(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\t')
			cmd[i] = ' ';
		i++;
	}
	return (cmd);
}
