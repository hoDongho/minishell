/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:42:27 by dhyun             #+#    #+#             */
/*   Updated: 2022/06/12 19:51:30 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
int		form_char(va_list ap, char form);
int		form_pointer(va_list ap, char form);
int		form_hexa(va_list ap, char form);
int		form_decimal(va_list ap);
int		form_unsigned_decimal(va_list ap);

#endif
