/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbetsey <bbetsey12@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:59:26 by bbetsey           #+#    #+#             */
/*   Updated: 2021/04/09 16:30:17 by bbetsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

typedef struct s_gnl
{
	char		*buf;
	char		*new_line;
	int			read_bytes;
}				t_gnl;

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const s2);
void	*ft_calloc(size_t count, size_t size);
char	*check_remain(char **remain, char **line);
void	append_line(char **buf, char **new_line, char **line, char **remain);
void	*ft_bzero(void *s, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *str);
size_t	ft_strlen(const char *str);

#endif
