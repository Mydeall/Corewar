/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 12:07:24 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/08 11:54:58 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_get_format	*make_format_tab(void)
{
	t_get_format	*format_tab;

	if (!(format_tab = (t_get_format*)malloc(sizeof(t_get_format) * 4)))
		return (NULL);
	format_tab[0].format = "#+-0 ";
	format_tab[0].f = &get_attributs;
	format_tab[1].format = "0123456789*";
	format_tab[1].f = &get_width;
	format_tab[2].format = ".";
	format_tab[2].f = &get_precision;
	format_tab[3].format = "hlL";
	format_tab[3].f = &get_modifier;
	return (format_tab);
}

t_call_format	*make_call_format(void)
{
	t_call_format *call_format;

	if (!(call_format = (t_call_format*)malloc(sizeof(t_call_format) * 5)))
		return (NULL);
	call_format[0].format = "diouxXpb";
	call_format[0].f = &int_format;
	call_format[1].format = "s";
	call_format[1].f = &str_format;
	call_format[2].format = "c";
	call_format[2].f = &char_format;
	call_format[3].format = "f";
	call_format[3].f = &double_format;
	call_format[4].format = "%";
	call_format[4].f = &percent_format;
	return (call_format);
}

t_attributs		*make_call_attr(void)
{
	t_attributs *call_attr;

	if (!(call_attr = (t_attributs*)malloc(sizeof(t_attributs) * 3)))
		return (NULL);
	call_attr[0].attr = '#';
	call_attr[0].f = &ft_hashtag;
	call_attr[1].attr = '+';
	call_attr[1].f = &ft_plus;
	call_attr[2].attr = ' ';
	call_attr[2].f = &ft_space;
	return (call_attr);
}
