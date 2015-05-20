/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 04:07:24 by tcoppin           #+#    #+#             */
/*   Updated: 2015/04/29 04:12:53 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		check_port_nb(char *str, char *bin)
{
	unsigned int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if ((i + 1) < ft_strlen(str))
	{
		ft_putendl(ft_strjoin(bin, " : The port must be an integer."));
		return (0);
	}
	return (1);
}

void	ft_usage_cl(char *str)
{
	ft_putendl(ft_strjoin(ft_strjoin("Usage : ", str), " <addr> <port>"));
	exit(-1);
}