#include "libasm.h"
#include <errno.h>

typedef struct s_readp
{
	int errno_value;
	ssize_t	ret;
}		t_readp;

t_readp read_p(char *buf, char *str, ssize_t (*reader)(int, void *, size_t))
{
	int		fds[2];
	ssize_t	ret;
	t_readp	readp;

	bzero(buf, BUFFER_SIZE);
	if (pipe(fds) < 0)
		exit(EXIT_FAILURE);
	fcntl(fds[0], F_SETFL, O_NONBLOCK);
	write(fds[1], str, strlen(str));
	errno = 0;
	readp.ret = reader(fds[0], buf, BUFFER_SIZE);
	readp.errno_value = errno;
	close(fds[1]);
	close(fds[0]);
	return (readp);
}

void	test_read(char *str)
{
	t_readp	my;
	char	buf_my[BUFFER_SIZE];
	t_readp	correct;
	char	buf_correct[BUFFER_SIZE];

	my = read_p(buf_my, str, &ft_read);
	correct = read_p(buf_correct, str, &read);
	if (my.errno_value != correct.errno_value || my.ret != correct.ret)
	{
		printf(KO);
		printf("Expected: errno: %i return: %li\n", correct.errno_value, correct.ret);
		printf("Got:      errno: %i return: %li\n", my.errno_value, my.ret);
		return ;
	}
	if (memcmp(buf_my, buf_correct, strlen(str)))
	{
		printf(KO);
		return ;
	}
	printf(OK);
}

void	test_strcmp(char *s1, char *s2)
{
	int	my;
	int	correct;

	my = ft_strcmp(s1, s2);
	correct = strcmp(s1, s2);
	if ((my > 0 && correct > 0) || (my < 0 && correct < 0) || (my == 0 && correct == 0))
		printf(OK);
	else
		printf("Expected: %i, got %i\n", correct, my);
}

void	test_strcpy(char *src)
{
	char	dest1[BUFFER_SIZE];
	char	dest2[BUFFER_SIZE];

	bzero(dest1, BUFFER_SIZE);
	bzero(dest2, BUFFER_SIZE);
	ft_strcpy(dest1, src);
	strcpy(dest2, src);
	if (!strcmp(dest1, dest2))
		printf(OK);
	else
		printf(KO);
}

void test_strdup(char *str)
{
	char	*str1;
	char	*str2;

	str1 = ft_strdup(str);
	str2 = strdup(str);
	if (!strcmp(str1, str2))
		printf(OK);
	else
		printf(KO);
	free(str1);
	free(str2);
}

void	test_strlen(char *str)
{
	int	my;
	int	correct;

	my = ft_strlen(str);
	correct = strlen(str);
	if (my == correct)
		printf(OK);
	else
		printf("Expected: %i, got %i\n", correct, my);
}

typedef struct s_writep
{
	int errno_value;
	ssize_t	ret;
}		t_writep;


t_writep write_p(char *buf, char *str, ssize_t (*writer)(int, const void *, size_t))
{
	int		fds[2];
	ssize_t	ret;
	t_writep	writep;

	bzero(buf, BUFFER_SIZE);
	if (pipe(fds) < 0)
		exit(EXIT_FAILURE);
	fcntl(fds[0], F_SETFL, O_NONBLOCK);
	errno = 0;
	writep.ret = writer(fds[1], buf, BUFFER_SIZE);
	writep.errno_value = errno;
	read(fds[0], buf, BUFFER_SIZE);
	close(fds[1]);
	close(fds[0]);
	return (writep);
}

void	test_write(char *str)
{
	t_writep	my;
	char		buf_my[BUFFER_SIZE];
	t_writep	correct;
	char		buf_correct[BUFFER_SIZE];

	my = write_p(buf_my, str, &ft_write);
	correct = write_p(buf_correct, str, &write);
	if (my.errno_value != correct.errno_value || my.ret != correct.ret)
	{
		printf(KO);
		printf("Expected: errno: %i return: %li\n", correct.errno_value, correct.ret);
		printf("Got:      errno: %i return: %li\n", my.errno_value, my.ret);
		return ;
	}
	if (memcmp(buf_my, buf_correct, strlen(str)))
	{
		printf(KO);
		return ;
	}
	printf(OK);
}
int		main(void)
{
	printf("ft_read\n");
	test_read("Hello World!");
	test_read("\0");
	test_read("");
	test_read("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	printf("\n");

	printf("ft_strcmp\n");
	test_strcmp("allo", "allo");
	test_strcmp("abcdef", "zcdef");
	test_strcmp("a", "");
	test_strcmp("", "a");
	test_strcmp("", "");
	test_strcmp("te\0", "\0");
	test_strcmp("\xff\xff", "\xff\xff");
	test_strcmp("\xff\x80", "\xff\x00");
	test_strcmp("\xff\xfe", "\xff");
	printf("\n");

	printf("ft_strcpy\n");
	test_strcpy("Hello World!");
	test_strcpy("\0");
	test_strcpy("");
	test_strcpy("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	printf("\n");

	printf("ft_write\n");
	test_write("Hello World!");
	test_write("\0");
	test_write("");
	test_write("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	printf("\n");

	printf("ft_strlen\n");
	test_strlen("Hello World!");
	test_strlen("\0");
	test_strlen("");
	test_strlen("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	printf("\n");

	printf("ft_strdup\n");
	test_strdup("Hello World!");
	test_strdup("\0");
	test_strdup("");
	test_strdup("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	printf("\n");
	return (0);
}
