/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:43:25 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/26 17:36:22 by dhyun            ###   ########seoul.kr  */
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
	return (pwd);
}

int	ft_pwd(t_envlist *envlist)
{
	char	*pwd;

	pwd = get_pwd(envlist);
	if (pwd == 0)
		return (1);
	printf("%s\n", pwd);
	g_data.exit_code = 0;
	return (0);
}
