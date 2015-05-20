/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 14:39:07 by tcoppin           #+#    #+#             */
/*   Updated: 2015/05/06 14:39:30 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_usage_cl(char *str)
{
	ft_putendl(ft_strjoin(ft_strjoin("Usage : ", str), " <addr> <port>"));
	exit(-1);
}