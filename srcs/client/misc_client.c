/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 19:31:12 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/03 08:37:20 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	ft_error_client(int i, char *str)
{
	if (i == USG)
	{
		ft_putstr_fd("\033[1;33mUsage : ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" <addr> <port>\033[00m", 2);
		exit(-1);
	}
	else if (i == OTH)
	{
		ft_putstr_fd("\033[1;33m", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("\033[00m", 2);
	}
}
