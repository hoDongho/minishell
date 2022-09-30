/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_re_dir_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:06:14 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/30 17:50:01 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_c_hd(int sig)
{
	sig = 0;
	g_data.exit_code = 1;
	g_data.hd = 1;
	printf("\n");
	close(STDIN_FILENO);
}

void	ft_sig_bs_hd(int sig)
{
	sig = 0;
	return ;
}

void	ft_read_heredoc(char *hd_input, char *hd_exit, int *new_in)
{
	while (1)
	{
		write(1, "> ", 2);
		hd_input = get_next_line(STDIN_FILENO);
		if (hd_input == 0)
			break ;
		if (ft_strcmp(hd_input, hd_exit) == 0)
			break ;
		write(*new_in, hd_input, ft_strlen(hd_input));
		free(hd_input);
	}
}

int	ft_here_doc(t_cmdnode *curr, int *new_in)
{
	char	*hd_exit;
	char	*hd_input;

	signal(SIGINT, ft_sig_c_hd);
	signal(SIGQUIT, ft_sig_bs_hd);
	g_data.hd = 0;
	if (*new_in != 0)
		close(*new_in);
	hd_exit = ft_strjoin(curr->next->str, "\n");
	hd_input = 0;
	*new_in = open("/tmp/.heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*new_in == -1)
		print_error("open", 1);
	ft_read_heredoc(hd_input, hd_exit, new_in);
	free(hd_exit);
	free(hd_input);
	close(*new_in);
	*new_in = open("/tmp/.heredoc_tmp", O_RDONLY, 0644);
	unlink("/tmp/.heredoc_tmp");
	return (g_data.hd);
}
