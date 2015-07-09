/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 20:03:33 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/13 15:01:40 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		read_server(t_client *all_c)
{
	int		r;

	r = 0;
	if ((r = recv(all_c->sock, all_c->buf, 2047, 0)) < 0)
	{
		ft_error_client(OTH, "Error in receiving the information.");
		r = 0;
	}
	all_c->buf[r] = '\0';
	return (r);
}

void	write_server(t_client *all_c, char *str)
{
	char	*sd;

	sd = ft_strjoin(str, "\n");
	if (send(all_c->sock, sd, ft_strlen(sd), 0) < 0)
		ft_error_client(OTH, "Error to send information.");
}
