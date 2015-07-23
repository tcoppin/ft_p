/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 17:42:39 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/24 01:31:43 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

t_serv	*ft_save_serv(t_serv *all_s)
{
	static t_serv	*s_all_s = NULL;

	if (all_s)
		s_all_s = all_s;
	return (s_all_s);
}

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

void	put_in_log(char *msg, t_serv *all_s)
{
	char	buffer[256];
	time_t	timestamp;

	timestamp = time(NULL);
	strftime(buffer, sizeof(buffer), "%d/%m/%y - %X : ", localtime(&timestamp));
	write(all_s->fd, buffer, ft_strlen(buffer));
	write(all_s->fd, msg, ft_strlen(msg));
}

void	ft_put_hist(t_cus *cus, int i, t_serv *all_s)
{
	char	*str;

	str = NULL;
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
	str = ft_strjoin("Execute \"", cus->buf);
	str = ft_strjoin_free(str, "\" by client ");
	str = ft_strjoin_free(str, ft_itoa(cus->cs));
	if (i > 0)
		str = ft_strjoin_free(str, " and it's a SUCCESS\n");
	else
		str = ft_strjoin_free(str, " and it's an ERROR\n");
	put_in_log(str, all_s);
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
