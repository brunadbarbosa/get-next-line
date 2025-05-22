/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmaria- <brmaria-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:00:29 by brmaria-          #+#    #+#             */
/*   Updated: 2025/05/20 11:56:43 by brmaria-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
size_t	ft_strl(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])	
	i++;
	return (i);
}

char	*ft_handle_nl(char *buffer, char *new_line)
{
	char	*final_line;
	int	nl_index;
	int	i;

	nl_index = ft_find_nl(new_line);
	if (nl_index >= 0)
	{
		i = -1;
	}
}

char	*ft_join_free(char *new_line, char *stash)
{
	char	*big_line;
	ssize_t	i;
	ssize_t	j;

	big_line = malloc(sizeof(char) * (ft_strl(new_line) +ft_strl(stash) + 1));
	if (big_line)
	{
		i = 0;
		j = 0;
		while (new_line[i])
		{
			big_line[i] = new_line[i];
			i++;
		}
		while (stash[j])
		{
			big_line[i + j] = stash[j];
			j++;
		}
		big_line[i + j] = '\0';	
	}
	free (new_line);
	return (big_line);
}

ssize_t	ft_find_nl(char *stash)
{
	size_t	i;

	i = 0;
	if (!stash)
		return (-1);
	while(stash[i])
	{
		if (stash[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_memmove_nl(char *stash)
{
	ssize_t	index;
	ssize_t	nl_index;

	index = 0;
	if(!stash)
		return ;
	nl_index = ft_find_nl(stash);
	if (nl_index == -1)
	{
		stash[0] = '\0';
		return ;
	}
	while (stash[index])
	{
		stash[index] = stash[index + nl_index + 1];
		index++;
	}
	while (index < BUFFER_SIZE)
	{
		stash[index] = '\0';
		index++;
	}
}

char    *ft_read_and_stash(int fd, char *stash, char *new_line)
{
        ssize_t b_read;
        char    *buffer;

	b_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
        if (!buffer)
                return (NULL);
	while (b_read > 0 && !ft_find_nl(stash))
	{
        	b_read = read(fd, buffer, BUFFER_SIZE);
		stash = ft_join_free(stash, buffer);
		new_line = ft_join_free(new_line, buffer);
	}
	free(buffer);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line = NULL;
	if (stash[0] != '\0')
		new_line = ft_join_free(new_line, stash);
	if (ft_find_nl(stash) >= 0)
		return (ft_handle_nl(stash, new_line));
	new_line = ft_read_and_stash(fd, stash, new_line);
	new_line = ft_handle_nl(stash, new_line);
	return (new_line);
}

#include <stdio.h>
# include <fcntl.h>

void	test(const char *file)
{
	// arquivos base:
	int		fd = open(file, O_RDONLY);
	char	*gnl = get_next_line(fd);

	while (gnl != NULL)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	if (gnl)
		free(gnl);
	close (fd);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Teste com somente um numero: \"./a.out x\"\n");
		printf("Teste 0 = lyrics.txt;\n");
		printf("Teste 1 = multilines.txt;\n");
		printf("Teste 2 = longline.txt;\n");
		printf("Teste 3 = no_newline.txt;\n");
		printf("Teste 4 = empty.txt;\n");
		printf("Teste 5 = just_newlines.txt;\n");
		printf("Teste 6 = single_newline.txt;\n");
		printf("Teste 7 = invalid fd.\n");
		return (1);
	}
	
	int	option = atoi(argv[1]);
	
	if (option == 0)
	{
		printf("====    Rap God, Eminem    ====\n\n");
		test("./main/tests/lyrics.txt");
	}
	
	else if (option == 1)
	{
		printf("==== Arquivo com várias linhas normais ====\n\n");
		test("./main/tests/multilines.txt");
	}

	else if (option == 2)
	{
		printf("==== Arquivo com linha muito longa ====\n\n");
		test("./main/tests/longline.txt");
	}

	else if (option == 3)
	{
		printf("==== Arquivo sem quebra de linha no final ====\n\n");
		test("./main/tests/no_newline.txt");
	}

	else if (option == 4)
	{
		printf("==== Arquivo vazio ====\n\n");
		test("./main/tests/empty.txt");
	}

	else if (option == 5)
	{
		printf("==== Arquivo com várias quebras de linha consecutivas ====\n\n");
		test("./main/tests/just_newlines.txt");
	}

	else if (option == 6)
	{
		printf("==== Arquivo com apenas um \\n ====\n\n");
		test("./main/tests/single_newline.txt");
	}

	else if (option == 7)
	{
		printf("==== File descriptor inválido ====\n\n");
		char *line = get_next_line(-1);
		if (!line)
			printf("fd tratado.\n");
		else
		{
			printf("fd nao tratado, retornando: %s\n", line);
			free(line);
		}
	}
	else
		printf("Escolha entre 0 e 7.\n");
    return (0);
}
