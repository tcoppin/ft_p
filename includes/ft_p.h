/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 17:37:04 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/04 12:39:26 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
# define FT_P_H

# include <dirent.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft.h"
# include "server.h"
# include "client.h"

typedef enum	e_error
{
	USG = 1,
	OTH,
}				t_error;

#endif
