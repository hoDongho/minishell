/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:43:25 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/14 12:45:59 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	errno = 0;
	pwd = getcwd(0, 0);
	if (pwd == 0) //error 처리?
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
