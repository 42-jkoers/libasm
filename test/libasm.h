#ifndef LIBASM_H
# define LIBASM_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# define OK		"\033[32m[OK]\033[0m\n"
# define KO		"\033[31m[KO]\033[0m\n"

# define BUFFER_SIZE 10000

ssize_t		ft_read(int fd, void *buf, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
ssize_t		ft_write(int fd, const void *buf, size_t n);

#endif
