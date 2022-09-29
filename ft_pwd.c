/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:43:25 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 21:10:21 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_envlist *envlist)
{
	char	*pwd;

	pwd = find_val(envlist, "PWD");
	if (pwd == 0)
	{
		pwd = getcwd(0, 0);
		if (pwd == 0)
		{
			print_error("getcwd", 1);
			return (0);
		}
		change_val(envlist, "PWD", pwd);
	}
	else
		pwd = ft_strdup(pwd);
	return (pwd);
}

int	ft_pwd(t_envlist *envlist)
{
	char	*pwd;

	pwd = get_pwd(envlist);
	if (pwd == 0)
		return (1);
	printf("%s\n", pwd);
	// unset PWD -> pwd command, (double free error) occurs
	// free(pwd);
	g_data.exit_code = 0;
	return (0);
}
