#ifndef GNL_H
# define GNL_H
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
