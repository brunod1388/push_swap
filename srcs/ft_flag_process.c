/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoncalv <bgoncalv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:43:07 by bgoncalv          #+#    #+#             */
/*   Updated: 2021/11/08 16:53:27 by bgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_get_flag(char *format, t_fdata *fdata)
{
	while (ft_ischarset(*(++format), FLAGS_LIST))
	{
		if (*format == '+')
			fdata->plus = 1;
		if (*format == '#')
			fdata->hash = 1;
		if (*format == '-')
			fdata->minus = 1;
		if (*format == ' ')
			fdata->space = 1;
		if (*format == '0')
			fdata->zero = 1;
	}
	return (format);
}

char *ft_eval_flags(char *format, t_fdata *fdata)
{
	ft_fdata_init(fdata);
	format = ft_get_flag(format, fdata);
	if (ft_isdigit(*format) && !fdata->precision)
		fdata->width = ft_atoi(format);
	while (ft_isdigit(*format))
		format++;
	if (*format == '.')
		fdata->dot = 1;
	if(format[0] == '.' && ft_isdigit(format[1]))
		fdata->precision = ft_atoi(++format);
	while (ft_isdigit(*format))
		format++;
	if (ft_ischarset(*format, FORMAT_LIST))
		fdata->type = *format;
	return (++format);
}

int	ft_width_process(t_fdata *fdata)
{
	if (fdata->width > fdata->clen)
	{
		if (fdata->minus)
		{
			if (ft_addsufix(fdata, ' ', fdata->width - fdata->clen) == -1)
				return (-1);
		}
		else if (fdata->zero)
		{
			if (ft_addprefix(fdata, '0', fdata->width - fdata->clen) == -1)
				return (-1);
		}
		else
		{
			if (ft_addprefix(fdata, ' ', fdata->width - fdata->clen) == -1)
				return (-1);
		}
	}
	return (fdata->clen);
}

int	ft_space_process(t_fdata *fdata)
{
	if (fdata->space && fdata->current[0] != ' ' &&
			!ft_memchr(fdata->current, '-', fdata->clen))
		ft_addprefix(fdata, ' ', 1);
	return (fdata->clen);
}

int	ft_hash_process(t_fdata *fdata)
{
	char *dst;

	if (fdata->type == 'p' || 
		(fdata->hash && (fdata->type == 'x' || fdata->type == 'X')))
	{
		dst = malloc(fdata->clen + 3);
		if (!dst)
			return (-1);
		dst[0] = '0';
		if (fdata->type == 'p' || fdata->type == 'x')
			dst[1] = 'x';
		else
			dst[1] = 'X';
		dst[2] = 0;
		ft_strcat(dst, fdata->current);
		free(fdata->current);
		fdata->current = dst;
		fdata->clen = ft_strlen(fdata->current);
	}
	return (fdata->clen);
}
