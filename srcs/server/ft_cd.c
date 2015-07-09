/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/01 18:32:19 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/03 16:47:22 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	echo_new_dir(t_cus *cus, int i)
{
	char	*str;
	char	*dir;

	if (i == 1)
	{
		if (ft_strequ(cus->cur_dir, "d_server"))
			str = ft_strdup("\033[1;34mNew working directory : /");
		else
		{
			dir = ft_strchr(cus->cur_dir, '/');
			str = ft_strjoin("\033[1;34mNew working directory : ", dir);
		}
		str = ft_strjoin_free(str, "\033[00m");
		write_client(cus, str);
		if (str)
			free(str);
	}
}

void	cd_redirect(t_cus *cus, t_serv *all_s, char *pwd)
{
	char	*tmp;

	write_client(cus, "\033[1;33mReturn to the working directory : /\033[00m");
	chdir(all_s->root);
	if (cus->old_dir)
		free(cus->old_dir);
	cus->old_dir = ft_strdup(pwd);
	tmp = NULL;
	pwd = getcwd(tmp, 1024);
	cus->cur_dir = ft_strdup(ft_strstr(pwd, "d_server"));
	if (pwd)
		free(pwd);
}

int		ft_sh_chdir(char *pwd, t_cus *cus, char *str, t_serv *all_s)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if (chdir(str) < 0)
		write_client(cus, "\033[1;33mNo such file or directory.\033[00m");
	else
	{
		if (cus->old_dir)
			free(cus->old_dir);
		cus->old_dir = ft_strdup(pwd);
		tmp = NULL;
		pwd = getcwd(tmp, 1024);
		cus->cur_dir = ft_strdup(ft_strstr(pwd, "d_server"));
		if (ft_strnequ(pwd, all_s->root, ft_strlen(all_s->root)) == 0\
			|| ft_strlen(pwd) < ft_strlen(all_s->root))
			cd_redirect(cus, all_s, pwd);
		else
			i = 1;
		if (pwd)
			free(pwd);
	}
	return (i);
}

int		ft_sh_cd_option(t_cus *cus, char *pwd, t_serv *all_s)
{
	if (cus->old_dir)
		return (ft_sh_chdir(pwd, cus, cus->old_dir, all_s));
	else
	{
		write_client(cus, "\033[1;33mNo such file or directory.\033[00m");
		return (-1);
	}
}

int		exec_cd(t_cus *cus, char **cmd_array, t_serv *all_s)
{
	char	*pwd;
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	pwd = getcwd(tmp, 1024);
	if (cmd_array[1] && !cmd_array[2])
	{
		if (cmd_array[1][0] == '-' && cmd_array[1][1])
			write_client(cus, "\033[1;33mUsage: cd [-][-|<dir>].\033[00m");
		else if (cmd_array[1][0] == '-')
			i = ft_sh_cd_option(cus, pwd, all_s);
		else
			i = ft_sh_chdir(pwd, cus, cmd_array[1], all_s);
	}
	else if (!cmd_array[1])
		i = ft_sh_chdir(pwd, cus, all_s->root, all_s);
	else
		ft_putendl_fd("\033[1;33mcd: Too many arguments.\033[00m", 2);
	if (pwd)
		free(pwd);
	echo_new_dir(cus, i);
	return (i);
}
