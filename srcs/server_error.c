/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 19:09:33 by tcoppin           #+#    #+#             */
/*   Updated: 2015/04/28 19:10:27 by tcoppin          ###   ########.fr       */
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
		ft_putendl(ft_strjoin(bin, " : The server port must be an integer."));
		return (0);
	}
	return (1);
}

int		check_port_range(int port, char *bin)
{
	char	*str;

	if (port <= 0)
	{
		ft_putendl(ft_strjoin(bin, " : port range not valid."));
		return (0);
	}
	else if (port < 1024)
	{
		str = ft_strjoin(bin, " : restriction on binding to ports < 1024.");
		ft_putendl(str);
		return (0);
	}	
	return (1);
}

void	ft_usage(char *str)
{
	ft_putendl(ft_strjoin(ft_strjoin("Usage : ", str), " <port>"));
	exit(-1);
}