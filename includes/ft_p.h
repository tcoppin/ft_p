/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/28 13:12:12 by tcoppin           #+#    #+#             */
/*   Updated: 2015/04/29 04:13:28 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>

/*
**	server_error.c
*/
int				check_port_nb(char *str, char *bin);
int				check_port_range(int port, char *bin);
void			ft_usage(char *str);

/*
**	client_error.c
*/
void			ft_usage_cl(char *str);
int				check_port_nb(char *str, char *bin);

/*
**	server.c
*/
int				create_server(int port);

#endif
