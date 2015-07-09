/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcoppin <tcoppin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/03 16:26:45 by tcoppin           #+#    #+#             */
/*   Updated: 2015/06/03 17:15:59 by tcoppin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	echo_new_dir_cl(t_client *all_c, int i)
{
	char	*str;
	char	*dir;

	if (i == 1)
	{
		if (ft_strequ(all_c->cur_dir, all_c->root))
			str = ft_strdup("\033[1;34mNew working directory : /");
		else
		{
			dir = ft_strchr(all_c->cur_dir, '/');
			str = ft_strjoin("\033[1;34mNew working directory : ", dir);
		}
		str = ft_strjoin_free(str, "\033[00m");
		ft_putendl(str);
		if (str)
			free(str);
	}
}

void	cd_redirect_cl(t_client *all_c, char *pwd)
{
	char	*tmp;

	ft_putendl("\033[1;33mReturn to the working directory : /\033[00m");
	chdir(all_c->src_dir);
	if (all_c->old_dir)
		free(all_c->old_dir);
	all_c->old_dir = ft_strdup(pwd);
	tmp = NULL;
	pwd = getcwd(tmp, 1024);
	all_c->cur_dir = ft_strdup(ft_strstr(pwd, all_c->root));
	if (pwd)
		free(pwd);
}

int		ft_sh_chdir_cl(char *pwd, t_client *all_c, char *str)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = -1;
	if (chdir(str) < 0)
		ft_putendl("\033[1;33mNo such file or directory.\033[00m");
	else
	{
		if (all_c->old_dir)
			free(all_c->old_dir);
		all_c->old_dir = ft_strdup(pwd);
		tmp = NULL;
		pwd = getcwd(tmp, 1024);
		all_c->cur_dir = ft_strdup(ft_strstr(pwd, all_c->root));
		if (ft_strnequ(pwd, all_c->src_dir, ft_strlen(all_c->src_dir)) == 0\
			|| ft_strlen(pwd) < ft_strlen(all_c->src_dir))
			cd_redirect_cl(all_c, pwd);
		else
			i = 1;
		if (pwd)
			free(pwd);
	}
	return (i);
}

int		ft_sh_cd_option_cl(t_client *all_c, char *pwd)
{
	if (all_c->old_dir)
		return (ft_sh_chdir_cl(pwd, all_c, all_c->old_dir));
	else
	{
		ft_putendl("\033[1;33mNo such file or directory.\033[00m");
		return (-1);
	}
}

int		exec_l_cd(t_client *all_c, char **cmd_array)
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
			ft_putendl("\033[1;33mUsage: cd [-][-|<dir>].\033[00m");
		else if (cmd_array[1][0] == '-')
			i = ft_sh_cd_option_cl(all_c, pwd);
		else
			i = ft_sh_chdir_cl(pwd, all_c, cmd_array[1]);
	}
	else if (!cmd_array[1])
		i = ft_sh_chdir_cl(pwd, all_c, all_c->src_dir);
	else
		ft_putendl_fd("\033[1;33mcd: Too many arguments.\033[00m", 2);
	if (pwd)
		free(pwd);
	echo_new_dir_cl(all_c, i);
	return (i);
}
