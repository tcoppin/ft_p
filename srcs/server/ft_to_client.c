/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 12:02:36 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/04 15:42:56 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		read_client(t_cus *cus)
{
	int		r;

	r = 0;
	if ((r = recv(cus->cs, cus->buf, 2048, 0)) < 0)
	{
		ft_error_server(OTH, "Error in receiving the information.");
		r = 0;
	}
	cus->buf[r - 1] = '\0';
	return (r);
}

void	write_client(t_cus *cus, char *str)
{
	char	*sd;

	sd = ft_strjoin(str, "\n");
	if (send(cus->cs, sd, ft_strlen(sd), 0) < 0)
		ft_error_server(OTH, "Error to send information.");
}
