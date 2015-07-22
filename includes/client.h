/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/30 17:39:03 by tcoppin           #+#    #+#             */
/*   Updated: 2015/07/22 16:54:20 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# define SOCKADDR const struct sockaddr

typedef struct	s_client
{
	int		port;
	char	*addr;
	int		sock;
	char	*line;
	char	buf[2048];
	char	*cur_dir;
	char	*old_dir;
	char	*root;
	char	*src_dir;
	int		quit;
}				t_client;

/*
**	CLIENT.C
*/
int				ft_put_prompt(t_client *all_c);

/*
**	INIT_CLIENT.C
*/
void			ft_init_client(t_client *all_c, char **av);
int				create_client(char *addr, t_client *all_c);

/*
**	FT_CHECK.C
*/
int				is_client(char **cmd_array, t_client *all_c, char *cmd_all);
void			check_cmd_cl(char **cmd_array, t_client *all_c, char *cmd_all);

/*
**	EXEC_CLIENT.C
*/
int				exec_get_cl(t_client *all_c, char *cmd_all, char **cmd_array);
int				exec_put_cl(t_client *all_c, char *cmd_all, char **cmd_array);
int				exec_l_cmd(char **cmd_array, char *bin);
int				exec_l_pwd(t_client *all_c, char **cmd_array);
int				exec_l_quit(t_client *all_c, char *cmd_all);

/*
**	FT_CD_CLIEN.C
*/
void			echo_new_dir_cl(t_client *all_c, int i);
void			cd_redirect_cl(t_client *all_c, char *pwd);
int				ft_sh_chdir_cl(char *pwd, t_client *all_c, char *str);
int				ft_sh_cd_option_cl(t_client *all_c, char *pwd);
int				exec_l_cd(t_client *all_c, char **cmd_array);

/*
**	FT_TO_SERVER.C
*/
int				read_server(t_client *all_c);
void			write_server(t_client *all_c, char *str);

/*
**	MISC_CLIENT.C
*/
void			ft_error_client(int i, char *str);

#endif
