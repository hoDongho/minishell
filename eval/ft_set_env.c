/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:57:28 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 17:24:50 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env(t_envlist *envlist, char **env)
{
	int				i;
	int				cnt;
	char			*key;

	i = 0;
	while (env[i])
	{
		key = env[i];
		cnt = 0;
		while (*key)
		{
			if (*key == '=')
				break ;
			cnt++;
			key++;
		}
		key = 0;
		key = ft_calloc(cnt + 1, sizeof(char));
		ft_memmove(key, env[i], cnt);
		ft_push_env(key, getenv(key), envlist);
		free(key);
		i++;
	}
}
