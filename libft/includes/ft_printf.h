/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:22:43 by pthan             #+#    #+#             */
/*   Updated: 2019/11/04 17:22:45 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# define BUFF_SIZE 128
# include <wchar.h>

/*
** To generate the same warnings as the real printf :
*/

# define PRINTFRET __attribute__ ((__format__(printf, 1, 2))) int

/*
** -------------------------------- FLAGS --------------------------------
*/

/*
** F_HASH  (1 << 0) --> '#'   0000 0000 0001  -->  alternate form ("0x", '0')
** F_SPACE (1 << 1) --> ' '   0000 0000 0010  -->  ' ' b4 positive number
** F_PLUS  (1 << 2) --> '+'   0000 0000 0100  -->  display sign of number
** F_MINUS (1 << 3) --> '-'   0000 0000 1000  -->  left justify/padding
** F_ZERO  (1 << 4) --> '0'   0000 0001 0000  -->  '0' padding
*/

# define F_HASH  (1 << 0)
# define F_SPACE (1 << 1)
# define F_PLUS  (1 << 2)
# define F_MINUS (1 << 3)
# define F_ZERO  (1 << 4)

/*
** --------------------------- LENGTH MODIFIERS --------------------------
*/

/*
** LM_SHORT  (1 << 5)  --> 'h'   0000 0010 0000  -->  short int/uint
** LM_LONG   (1 << 6)  --> 'l'   0000 0100 0000  -->  long  int/uint
** LM_DOUBLE (1 << 7)  --> 'L'   0000 1000 0000  -->  double (floats)
** LM_INTMAX (1 << 8)  --> 'j'   0001 0000 0000  -->  intmax_t/uintmax_t
** LM_SIZE_T (1 << 9)  --> 'z'   0010 0000 0000  -->  ssize_t/size_t
** LM_CHAR   (1 << 10) --> 'hh'  0100 0000 0000  -->  signed/unsigned char
** LM_LONG2  (1 << 11) --> 'll'  1000 0000 0000  -->  long long int/uint
*/

# define LM_SHORT  (1 << 5)
# define LM_LONG   (1 << 6)
# define LM_DOUBLE (1 << 7)
# define LM_INTMAX (1 << 8)
# define LM_SIZE_T (1 << 9)
# define LM_CHAR   (1 << 10)
# define LM_LONG2  (1 << 11)

/*
** -------------------------------- BASES --------------------------------
*/

# define B_DEC 10
# define B_BIN (1 << 1)
# define B_OCT (1 << 3)
# define B_HEX (1 << 4)

/*
** -------------------------------- COLORS -------------------------------
*/

# define C_BOLD		    "\033[1m"
# define C_UNDERLINE    "\033[4m"
# define C_BLACK		"\033[30m"
# define C_RED			"\033[31m"
# define C_GREEN		"\033[32m"
# define C_YELLOW		"\033[33m"
# define C_BLUE			"\033[34m"
# define C_PURPLE		"\033[35m"
# define C_CYAN			"\033[36m"
# define C_WHITE		"\033[37m"

/*
** -------------------------------- STRUCT -------------------------------
*/

typedef struct	s_printf
{
	int			ret;
	int			fd;
	int			flags;
	int			min_len;
	int			precision;
	int			base;
	int			neg;
	int			pad;
	int			buff_i;
	char		buff[BUFF_SIZE];
	char		*format;
	char		conv;
	va_list		ap;
}				t_printf;

typedef	void(*t_f_conv)(t_printf*);

typedef struct	s_conv
{
	char		*c;
	t_f_conv	funct;
}				t_conv;

/*
** ------------------------------- PRINTF -------------------------------
*/

PRINTFRET		ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

void			reset_struct(t_printf *pf);
void			color_or_char(t_printf *pf);
char			*color(t_printf *pf);

/*
** ------------------------------- PARSING -------------------------------
*/

int				parse_arg(t_printf *pf);

/*
** ------------------------------ CONVERSIONS ----------------------------
*/

int				is_conv(t_printf *pf);
int				conv_to_fct(t_printf *pf);
int				get_conversion(t_printf *pf);

/*
** ----------------------------- BUFF MANAGER ----------------------------
*/

void			reset_buff(t_printf *pf);
void			check_buff(t_printf *pf);
void			buffer(t_printf *pf, char *str, int i, int len);
void			wstr_tobuff(t_printf *pf, wchar_t *str, int len);
void			end(t_printf *pf);

/*
** ------------------------------ PADDING --------------------------------
*/

void			hash_padding(t_printf *pf);
void			min_padding(t_printf *pf, char c, int len);
void			char_padding(t_printf *pf, char c);

/*
** ---------------------------- CHECKS FLAGS -----------------------------
*/

void			plus_flag_pad(t_printf *pf, int len);
void			zero_flag_pad(t_printf *pf, int len);
void			hash_flag_pad(t_printf *pf, int nb);

/*
** ------------------------------ NUMBERS --------------------------------
*/

void			ft_castconvint(t_printf *pf);
void			ft_castconvuox(t_printf *pf);
void			int_conv(t_printf *pf, intmax_t nb);
void			uint_conv(t_printf *pf, uintmax_t nb);
void			ox_conv(t_printf *pf, uintmax_t nb);
uintmax_t		treat_negaspos(t_printf *pf, intmax_t nb);

/*
** ------------------------------- FLOATS -------------------------------
*/

void			float_conv(t_printf *pf);
void			f_conv(t_printf *pf, long double nb);

/*
** ---------------------------- CHAR & STRINGS ---------------------------
*/

void			char_conv(t_printf *pf);
void			wchar_conv(t_printf *pf);
void			str_conv(t_printf *pf);
void			wstr_conv(t_printf *pf);
size_t			wslen_tobuff(wchar_t *s, int wslen);

/*
** ----------------------------  %  & ptr address ------------------------
*/

void			print_pct(t_printf *pf);
void			print_ptr_add(t_printf *pf);

/*
** -------------------------------- UTILS --------------------------------
*/

char			*to_upper(char *str);
char			*ft_lltoa_base(uintmax_t nb, intmax_t base);
char			*ft_get_wchar(wint_t wc);
char			find_conv(char *str, char c);
int				ft_nbrlen(uintmax_t nb, intmax_t base);
int				find_flag(char *str, char c);
int				ft_isnan(long double nb);
int				ft_isinf(long double nb);
size_t			ft_wcharlen(wint_t wc);
size_t			ft_wstrlen(wchar_t *s);
intmax_t		pow_ten(intmax_t nb, int n);

#endif
