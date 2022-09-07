/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_form.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:46:53 by dhyun             #+#    #+#             */
/*   Updated: 2022/06/03 01:20:47 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	form_char(va_list ap, char form)
{
	int		len;
	char	temp_c;
	char	*temp_s;

	len = 0;
	if (form == 'c')
	{
		temp_c = va_arg(ap, int);
		write (1, &temp_c, 1);
		return (1);
	}
	else if (form == 's')
	{
		temp_s = va_arg(ap, char *);
		if (temp_s == 0)
			temp_s = "(null)";
		len = ft_strlen(temp_s);
		ft_putstr_fd(temp_s, 1);
		return (len);
	}
	return (0);
}

int	form_pointer(va_list ap, char form)
{
	int					len;
	char				*convert_temp_p;
	unsigned long long	temp_p;

	len = 0;
	temp_p = va_arg(ap, unsigned long long);
	convert_temp_p = ft_itoa_hexa(temp_p, form);
	len = ft_strlen(convert_temp_p);
	ft_putstr_fd(convert_temp_p, 1);
	free (convert_temp_p);
	return (len);
}

int	form_hexa(va_list ap, char form)
{
	int				len;
	char			*convert_temp_x;
	unsigned int	temp_x;

	len = 0;
	temp_x = va_arg(ap, unsigned int);
	convert_temp_x = ft_itoa_hexa(temp_x, form);
	while (convert_temp_x[len] != 0)
	{
		if (form == 'X')
			convert_temp_x[len] = ft_toupper(convert_temp_x[len]);
		len++;
	}
	ft_putstr_fd(convert_temp_x, 1);
	free(convert_temp_x);
	return (len);
}

int	form_decimal(va_list ap)
{
	int		len;
	char	*convert_temp_d;
	int		temp_d;

	len = 0;
	temp_d = va_arg(ap, int);
	convert_temp_d = ft_itoa(temp_d);
	len = ft_strlen(convert_temp_d);
	ft_putstr_fd(convert_temp_d, 1);
	free(convert_temp_d);
	return (len);
}

int	form_unsigned_decimal(va_list ap)
{
	int				len;
	char			*convert_temp_u;
	unsigned int	temp_u;

	len = 0;
	temp_u = va_arg(ap, unsigned int);
	convert_temp_u = ft_itoa_unsigned(temp_u);
	len = ft_strlen(convert_temp_u);
	ft_putstr_fd(convert_temp_u, 1);
	free(convert_temp_u);
	return (len);
}
