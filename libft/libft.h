/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszikora <bszikora@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:37:51 by bszikora          #+#    #+#             */
/*   Updated: 2024/03/16 16:39:09 by bszikora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

typedef unsigned long long	t_size_t;
typedef struct s_list
{
	void					*content;
	struct s_list			*next;
}							t_list;

char						*ft_strjoin(char const *s1, char const *s2);
char						*ft_substr(char const *s, unsigned int start,
								t_size_t len);
void						ft_bzero(void *str, t_size_t len);
int							ft_isalnum(int i);
int							ft_isalpha(int i);
int							ft_isascii(int i);
int							ft_isdigit(int i);
int							ft_isprint(int i);
void						*ft_memchr(const void *s, int c, t_size_t n);
void						*ft_memcpy(void *dst, const void *src, t_size_t n);
void						*ft_memmove(void *dst, const void *src,
								t_size_t len);
void						*ft_memset(void *str, int c, t_size_t len);
char						*ft_strchr(const char *s, int c);
t_size_t					ft_strlcat(char *dst, const char *src,
								t_size_t dstsize);
t_size_t					ft_strlcpy(char *dst, const char *src,
								t_size_t dstsize);
int							ft_strlen(const char *str);
int							ft_strncmp(const char *s1, const char *s2,
								t_size_t n);
char						*ft_strrchr(const char *s, int c);
int							ft_tolower(int c);
int							ft_toupper(int c);
int							ft_atoi(const char *str);
void						*ft_calloc(t_size_t count, t_size_t size);
int							ft_memcmp(const void *s1, const void *s2,
								t_size_t n);
char						*ft_strdup(const char *s1);
char						*ft_strnstr(const char *h, const char *n,
								t_size_t l);
char						*ft_itoa(int n);
void						ft_putchar_fd(char c, int fd);
void						ft_putendl_fd(char *s, int fd);
void						ft_putnbr_fd(int n, int fd);
char						**ft_split(char const *s, char c);
void						ft_striteri(char *s, void (*f)
								(unsigned int, char *));
char						*ft_strmapi(char const *s, char (*f)
								(unsigned int, char));
char						*ft_strtrim(char const *s1, char const *set);
void						ft_putstr_fd(char *s, int fd);
#endif