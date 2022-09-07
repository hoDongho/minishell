/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:57:45 by dhyun             #+#    #+#             */
/*   Updated: 2022/07/17 22:48:13 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	find_pos(char *str, int pos)
{
	while (str[pos] != 0)
	{
		if ((str[pos] == '\'' || str[pos] == '\"') && str[pos - 1] != '\\')
			break ;
		pos++;
	}
	return (pos);
}

char	*rm_quote(t_opt *opt, char *str, char *tmp)
{
	char	*tmp_free;

	opt->start = find_pos(str, 0);
	opt->end = find_pos(str, opt->start + 1);
	while (str[opt->end] != str[opt->start])
		opt->end = find_pos(str, opt->end + 1);
	opt->len = opt->end - opt->start - opt->bs;
	tmp = ft_substr_free(tmp, opt->start + 1, opt->len - 1);
	if (ft_strncmp(str, "./", 2) == 0)
	{
		tmp_free = tmp;
		tmp = ft_strjoin("./", tmp);
		free(tmp_free);
	}
	if (tmp == 0)
		print_error("malloc", 1);
	return (tmp);
}

char	*rm_backslash(t_opt *opt, char *str)
{
	char	*tmp;
	char	**tmp_split;
	int		i;

	i = 0;
	tmp = 0;
	if (ft_strchr(str, '\\') != 0)
	{
		tmp_split = ft_split(str, '\\');
		if (tmp_split == 0)
			print_error("split", 1);
		while (tmp_split[i] != 0)
		{
			tmp = ft_strjoin2(tmp, tmp_split[i++]);
			if (tmp == 0)
				print_error("malloc", 1);
		}
		opt->bs = i - 1;
		free_split(tmp_split);
	}
	else
		tmp = ft_strdup(str);
	if (tmp == 0)
		print_error("malloc", 1);
	return (tmp);
}

void	set_s_cmds(t_cmd *cmds, char *str, char *tmp)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strchr(str, ' ') != 0)
		len = len - ft_strlen(ft_strchr(str, ' '));
	if (ft_strncmp(str, "./", 2) != 0)
	{
		cmds->s_cmds = (char **)malloc(sizeof(char *) * 3);
		if (cmds->s_cmds == 0)
			print_error("malloc", 1);
		cmds->s_cmds[0] = ft_substr(str, 0, len);
		if (cmds->s_cmds[0] == 0)
			print_error("malloc", 1);
		cmds->s_cmds[1] = tmp;
		cmds->s_cmds[2] = 0;
	}
	else
	{
		cmds->s_cmds = (char **)malloc(sizeof(char *) * 2);
		if (cmds->s_cmds == 0)
			print_error("malloc", 1);
		cmds->s_cmds[0] = tmp;
		cmds->s_cmds[1] = 0;
	}
}

void	set_option(t_cmd *cmds, char *str)
{
	t_opt	opt;
	char	*tmp;

	init_opt(&opt);
	tmp = rm_backslash(&opt, str);
	if (check_quote(str) == 0)
		tmp = rm_quote(&opt, str, tmp);
	set_s_cmds(cmds, str, tmp);
}
