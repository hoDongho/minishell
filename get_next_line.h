/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:47:57 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/23 15:32:13 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
size_t	ft_strlen2(const char *s);
char	*ft_strchr2(const char *s, int c);
void	*ft_memmove2(void *dst, const void *src, size_t len);
char	*ft_strdup2(const char *s1);
char	*ft_strjoin2(char *s1, char *s2);

#endif
