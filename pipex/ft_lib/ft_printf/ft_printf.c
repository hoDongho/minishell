/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:41:27 by dhyun             #+#    #+#             */
/*   Updated: 2022/05/19 19:18:55 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

char	check_form(char form)
{
	if (form == 'c' || form == 's' || form == 'p'
		|| form == 'd' || form == 'i' || form == 'u'
		|| form == 'x' || form == 'X' || form == '%')
		return (form);
	return ('f');
}

int	print_form(va_list ap, char form)
{
	int	len;

	len = 1;
	if (form == 'c' || form == 's')
		len = form_char(ap, form);
	else if (form == 'p')
		len = form_pointer(ap, form);
	else if (form == 'x' || form == 'X')
		len = form_hexa(ap, form);
	else if (form == 'd' || form == 'i')
		len = form_decimal(ap);
	else if (form == 'u')
		len = form_unsigned_decimal(ap);
	else if (form == '%')
		write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	i;
	int		len;
	char	form;

	i = 0;
	len = 0;
	va_start(ap, format);
	while (format[i] != 0)
	{
		if (format[i] == '%')
		{
			form = check_form(format[++i]);
			if (form == 'f')
				return (-1);
			len += print_form(ap, form) - 2;
			i++;
		}
		else if (format[i] != 0)
			write(1, &format[i++], 1);
	}
	len += i;
	va_end(ap);
	return (len);
}
