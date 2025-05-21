/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:00:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/05/21 21:02:54 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	int	count;
	
	count = 0;
	while (c[count])
		count++;
	return (count);
}

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;
	
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	i = 0;
	if (!d && !s)
		return (NULL);
	if (d > s)
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ns;
	int	size;
	
	i = 0;
	j = 0;
	if(!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return(NULL);
		s1[0] = '\0';
	}
	size = ft_strlen(s1) + ft_strlen(s2);
	ns = malloc((size + 1) * sizeof(char));
	if (!ns)
		return (0);
	while ((i < size) && s1[i])
	{
		ns[i] = s1[i];
		i++;
	}
	while ((i < size) && s2[j])
	{
		ns[i + j] = s2[j];
		j++; 
	}
	ns[i + j] = '\0';
	free (s1);
	return (ns);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	unsigned char	cc;

	i = 0;
	cc = c;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char*)&s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char*)&s[i]);
	return (NULL);
}

char	*read_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	b_read;
	
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	b_read = read(fd, buffer, BUFFER_SIZE);
	if (b_read <= 0) 
	{
		free (buffer);
		return (NULL);
	}
	stash = ft_strjoin(stash, buffer);
	free (buffer);
	return (stash);
}

char	*find_nl(char *stash)
{
	int	i;
	char	*new_line;

	i = 0;
	while (stash[i] && !ft_strchr(stash, '\n'))
	{
		new_line[i] = stash[i];
		i++;
	}
	new_line[i] = '\n';
	i++;
	new_line = '\0';
	//stash = ft_memmove(stash, new_line, i);
	return (new_line);
}
char	*get_next_line(int fd)
{
	static char	*stash;
	char	*line;
	line = read_stash(fd, stash);
	line = find_nl(stash);
	return (line);
}


// #include <stdio.h>

// void	test(const char *file)
// {
// 	// arquivos base:
// 	int		fd = open(file, O_RDONLY);
// 	char	*gnl = get_next_line(fd);

// 	while (gnl != NULL)
// 	{
// 		printf("%s", gnl);
// 		free(gnl);
// 		gnl = get_next_line(fd);
// 	}
// 	if (gnl)
// 		free(gnl);
// 	close (fd);
// }

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 	{
// 		printf("Teste com somente um numero: \"./a.out x\"\n");
// 		printf("Teste 0 = lyrics.txt;\n");
// 		printf("Teste 1 = multilines.txt;\n");
// 		printf("Teste 2 = longline.txt;\n");
// 		printf("Teste 3 = no_newline.txt;\n");
// 		printf("Teste 4 = empty.txt;\n");
// 		printf("Teste 5 = just_newlines.txt;\n");
// 		printf("Teste 6 = single_newline.txt;\n");
// 		printf("Teste 7 = invalid fd.\n");
// 		return (1);
// 	}
	
// 	int	option = atoi(argv[1]);
	
// 	if (option == 0)
// 	{
// 		printf("====    Rap God, Eminem    ====\n\n");
// 		test("./main/tests/lyrics.txt");
// 	}
	
// 	else if (option == 1)
// 	{
// 		printf("==== Arquivo com várias linhas normais ====\n\n");
// 		test("./main/tests/multilines.txt");
// 	}

// 	else if (option == 2)
// 	{
// 		printf("==== Arquivo com linha muito longa ====\n\n");
// 		test("./main/tests/longline.txt");
// 	}

// 	else if (option == 3)
// 	{
// 		printf("==== Arquivo sem quebra de linha no final ====\n\n");
// 		test("./main/tests/no_newline.txt");
// 	}

// 	else if (option == 4)
// 	{
// 		printf("==== Arquivo vazio ====\n\n");
// 		test("./main/tests/empty.txt");
// 	}

// 	else if (option == 5)
// 	{
// 		printf("==== Arquivo com várias quebras de linha consecutivas ====\n\n");
// 		test("./main/tests/just_newlines.txt");
// 	}

// 	else if (option == 6)
// 	{
// 		printf("==== Arquivo com apenas um \\n ====\n\n");
// 		test("./main/tests/single_newline.txt");
// 	}

// 	else if (option == 7)
// 	{
// 		printf("==== File descriptor inválido ====\n\n");
// 		char *line = get_next_line(-1);
// 		if (!line)
// 			printf("fd tratado.\n");
// 		else
// 		{
// 			printf("fd nao tratado, retornando: %s\n", line);
// 			free(line);
// 		}
// 	}
// 	else
// 		printf("Escolha entre 0 e 7.\n");
//     return (0);
// }
