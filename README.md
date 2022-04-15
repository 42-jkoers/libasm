# libasm

This 42's curriculum project implements the following C standard functions in x64 assembly (Intel)

```c
int		ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *dst, const char *src);
ssize_t		ft_write(int fd, const void *buf, size_t nbyte);
ssize_t		ft_read(int fd, void *buf, size_t nbyte);
char		*ft_strdup(const char *s1);
```

## Usage
```
make
make test
```
