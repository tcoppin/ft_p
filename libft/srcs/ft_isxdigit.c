/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 12:18:10 by tcoppin           #+#    #+#             */
/*   Updated: 2014/11/19 04:24:49 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isxdigit(int c)
{
	int rsl;

	rsl = 0;
	if ((c >= 65 && c <= 70) || (c >= 97 && c <= 102) || ft_isdigit(c) == 1)
		rsl = 1;
	return (rsl);
}
