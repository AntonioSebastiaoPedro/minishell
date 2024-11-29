/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:38 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/29 06:42:02 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 1023
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct t_stack
{
	int				value;
	int				index;
	struct t_stack	*next;
}					t_stack;

char				*get_next_line(int fd);
char				*ft_join_free_str(char *s1, char *s2);
void				ft_lstclear(t_stack **head);
void				ft_lstprint(t_stack *head);
t_stack				*ft_lstnew(int content);
t_stack				*ft_lstmin(t_stack *head);
t_stack				*ft_lstmax(t_stack *head);
t_stack				*ft_lstlast(t_stack *head);
t_stack				*ft_lstlastprev(t_stack *head);
void				ft_lstupdateindx(t_stack *head);
void				ft_lstadd_back(t_stack **head, t_stack *new_node);
int					ft_isint(char *str);
int					ft_isempty(char *str);
int					ft_tablen(char **tab);

long int			ft_strtol(char *str, char **endptr);
int					ft_lstissorted(t_stack *stack);
int					ft_lstsize(t_stack *lst);
int					ft_lstgetindex(t_stack **head, t_stack *value);
void				ft_freearray(char **array);
void				ft_puterror(void);
void				ft_lstdelone(t_stack *node);
void				ft_bzero(void *s, size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *ptr, int value, size_t size);
void				*ft_calloc(size_t num, size_t size);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void				*ft_memchr(const void *ptr, int value, size_t num);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_isalnum(int c);
int					ft_isspace(char ch);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isascii(int c);
int					ft_atoi(const char *str);
int					ft_isword(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);
char				*get_next_line(int fd);
char				**ft_split(char const *str, char c);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(const char *s);
char				*ft_strchr(const char *str, int c);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strrchr(const char *str, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strjoin_delimiter(char const *s1, char const delim,
						char const *s2);
char				*ft_strtok(char *env_path, const char delim,
						char **next_path);
char				*ft_strtok_2(char *str, const char *delimiter);
char				*ft_strappend(char *dest, const char *src);
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
#endif
