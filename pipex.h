/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:32:06 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/29 11:54:21 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "get_next_line.h"

char	*ft_strjoin_wc(char *s1, char *s2, char c);
void	print_error(char *str, int code);
int		check_access(char *tmp);

#endif
