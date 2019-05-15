/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 17:28:29 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/08 11:55:29 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <string.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 1000

typedef unsigned long long int	t_ulli;

typedef struct		s_stack
{
	char			*attributs;
	int				width;
	int				precision;
	char			*modifier;
	char			format;
}					t_stack;

typedef struct		s_attributs
{
	char			attr;
	int				(*f)(char**, t_stack*, int);
}					t_attributs;

typedef struct		s_get_format
{
	char			*format;
	int				(*f)(t_stack*, const char * restrict, int*, va_list);
}					t_get_format;

typedef struct		s_call_format
{
	char			*format;
	int				(*f)(va_list, t_stack*, char**);
}					t_call_format;

typedef struct		s_struct_tab
{
	t_stack			stack;
	t_get_format	*format_tab;
	t_attributs		*call_attr;
	t_call_format	*call_format;
	char			*buff;
}					t_struct_tab;

void				print_node(t_stack *current);
void				node_reset(t_stack *lst);
void				free_node(t_stack *lst);
int					ft_printf(const char *restrict format, ...);
void				concat_buff(char **buff, char *str, int i,\
		int *len);
int					ft_format_parser(const char *restrict format,\
		t_stack *new, t_struct_tab struct_tab, va_list ap);
int					get_attributs(t_stack *new, const char *restrict format,\
		int *i, va_list ap);
int					get_width(t_stack *new, const char *restrict format,\
		int *i, va_list ap);
int					get_precision(t_stack *new, const char *restrict format,\
		int *i, va_list ap);
int					get_modifier(t_stack *new, const char *restrict format,\
		int *i, va_list ap);
int					ft_stack_applier(t_stack *stack, t_struct_tab struct_tab,\
		va_list ap, int *len);
int					int_format(va_list ap, t_stack *stack, char **result);
int					str_format(va_list ap, t_stack *stack, char **result);
int					double_format(va_list ap, t_stack *stack, char **result);
int					char_format(va_list ap, t_stack *stack, char **result);
int					percent_format(va_list ap, t_stack *stack, char **result);
t_attributs			*make_call_attr(void);
t_call_format		*make_call_format(void);
t_get_format		*make_format_tab(void);
char				*precision(char *result, t_stack *stack);
char				*double_precision(char *result, int precision, int len);
long long int		int_modifier(t_ulli arg, t_stack *stack);
t_ulli				unsigned_modifier(t_ulli arg, t_stack *stack);
long double			f_modifier(long double arg, t_stack *stack);
char				*unsigned_conversion(t_ulli arg, t_stack *stack);
int					ft_width(char **result, t_stack *stack, int len_arg);
int					ft_hashtag(char **result, t_stack *stack, int len_arg);
int					ft_plus(char **result, t_stack *stack, int len_arg);
int					ft_space(char **result, t_stack *stack, int len_arg);

size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
long long int		ft_atoi(const char *str);
char				*ft_strcpy(char *dest, const char *src);
void				*ft_memset (void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s1);
void				*ft_memalloc(size_t size);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const*s1, char const *s2);
char				*ft_itoa(long long int n);
int					ft_pow(int nb, int pow);
char				*ft_itoa_base(unsigned long long int nb, const char *base);
char				*ft_dtoa(long double n, int precision);

#endif
