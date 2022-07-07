/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncaba <nathancaba.etu@outlook.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:48:38 by ncaba             #+#    #+#             */
/*   Updated: 2022/05/06 15:16:35 by ncaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"

# define STRING		1
# define U_INT		2
# define INT		3
# define HEX_UP		4
# define HEX_LOW	5
# define CHAR		6
# define PERCENT	7
# define POINTER	8

/*
** Descroption de la structure t_flags
** t_boolean    is_alternative:     Modifie les flags "oxXaAeEfFgG"
** t_boolean    is_padded_zero:     Ajoute nb_space fois '0' a gauche
** t_boolean    is_padded_left:     Justifie la string a gauche
** t_boolean    is_single_space:    Ajoute un espace unique a gauche
** t_boolean    is_plus:            si entier signé positif rajoute un +
** int          nb_space:           Ajoute des espaces justifiable
** int          nb_dec:             Définis le nombre max de decimale
*/

typedef struct s_flags
{
	t_boolean	is_alternative;
	t_boolean	is_padded_zero;
	t_boolean	is_padded_left;
	t_boolean	is_single_space;
	t_boolean	is_plus;
	int			nb_spaces;
	int			nb_dec;
}				t_flags;

int				ft_printf(char *str, ...);
int				ft_printf_fd(int fd, char *str, ...);
int				ft_grab_type(char **str, t_flags *flags, va_list params);
int				get_type(int *type, int p);
int				sort_letters(char c);
char			*ft_parse(char **str, va_list params, int *len);
char			*ft_itoa_base(long long n, char *base);
void			get_neg(long long *n, int *neg);
void			ft_decimal_check(char *str, t_flags *flags,
					int *loop, va_list params);
void			ft_spacing_check(char *str, t_flags *flags,
					int *loop, va_list params);
void			ft_add_padd(char **str, t_flags flags, int type);
void			ft_add_space(char **str, t_flags flags, int type);
void			ft_add_precis(char **str, t_flags flags);
void			ft_alternative(char **str, t_flags flags, int type);
char			*brancher(int type, t_flags flags, va_list params, int *len);
char			*ft_convert_string(t_flags flags, va_list params);
char			*ft_convert_pointer(t_flags flags, va_list params);
char			*ft_convert_int(t_flags flags, va_list params);
char			*ft_convert_hexa(t_flags flags, va_list params,
					t_boolean is_up);
char			*ft_convert_char(t_flags flags, va_list params, int *len);
char			*ft_convert_percent(t_flags flags);
char			*ft_convert_unsigned(t_flags flags, va_list params);

#endif
