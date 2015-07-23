/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 17:38:36 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/23 15:41:34 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

typedef struct	s_serv
{
	int		port;
	int		sock;
	int		cs;
	int		fd;
	char	*dir;
	char	*root;
}				t_serv;

typedef struct	s_cus
{
	int		cs;
	pid_t	pid;
	char	*cur_dir;
	char	*old_dir;
	char	buf[2048];
}				t_cus;

/*
**	SERVER.C
*/
void			server_app(t_cus *cus, t_serv *all_s);
void			connect_cus(t_serv *all_s);

/*
**	INIT_SERVER.C
*/
void			ft_init_serv(t_serv *all_s, char **av);
int				create_server(t_serv *all_s);
void			init_client(t_cus *cus, t_serv *all_s);

/*
**	FT_CHECK.C
*/
int				is_builtin(char **cmd_array, t_cus *cus, t_serv *all_s);
int				is_binary(char **cmd_array, t_cus *cus);
void			check_cmd(char **cmd_array, t_cus *cus, t_serv *all_s);

/*
**	FT_CD.C
*/
int				exec_cd(t_cus *cus, char **cmd_array, t_serv *all_s);
void			echo_new_dir(t_cus *cus, int i);
void			cd_redirect(t_cus *cus, t_serv *all_s, char *pwd);
int				ft_sh_chdir(char *pwd, t_cus *cus, char *str, t_serv *all_s);
int				ft_sh_cd_option(t_cus *cus, char *pwd, t_serv *all_s);

/*
**	GET_SERVER.C
*/
int				exec_get(t_cus *cus, char **cmd_array);

/*
**	EXEC_SERVER.C
*/
int				exec_put(t_cus *cus, char **cmd_array);
int				exec_cmd(t_cus *cus, char **cmd_array, char *bin);
int				exec_pwd(t_cus *cus, char **cmd_array, t_serv *all_s);

/*
**	FT_TO_CLIENT.C
*/
void			write_client(t_cus *cus, char *str);
int				read_client(t_cus *cus);

/*
**	MISC_SERVER.C
*/
void			put_in_log(char *msg, t_serv *all_s);
void			ft_error_server(int i, char *str);
char			*ft_leave_tab(char *cmd);
void			ft_put_hist(t_cus *cus, int i, t_serv *all_s);

#endif
