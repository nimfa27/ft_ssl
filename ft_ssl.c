/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdenisov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:06:47 by kdenisov          #+#    #+#             */
/*   Updated: 2019/05/20 11:06:50 by kdenisov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		check_error(t_flg *flg, char *arg, int fd)
{
	struct stat	statbuf;

	fstat(fd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		ft_printf("%s: %s: Is a directory\n", flg->alg, arg);
		return (-1);
	}
	if (fd < 0)
		ft_printf("%s: %s: No such file or directory\n", flg->alg, arg);
	return (fd);
}

int		parse_file(t_flg *flg, t_alp *al, char *arg, int fd)
{
	char		*line;
	char		*str;
	int			len;

	len = 0;
	fd = open(arg, O_RDONLY);
	if (check_error(flg, arg, fd) < 0)
		return (1);
	else
	{
		flg->fdname = arg;
		str = ft_strdup("");
		line = ft_strnew(BLOCK_SIZE);
		while ((len = read(fd, line, BLOCK_SIZE)) > 0)
		{
			line[len] = '\0';
			str = ft_strjoin(str, line);
		}
		ft_strdel(&line);
		close(fd);
		g_disp[flg->index](flg, al, str, len);
	}
	return (0);
}

void	parse_stdin(t_flg *flg, t_alp *al)
{
	char	*line;
	char	*str;
	int		len;

	len = 0;
	flg->in = 1;
	str = ft_strdup("");
	line = ft_strnew(BLOCK_SIZE);
	len = read(0, line, BLOCK_SIZE);
	while (len > 0)
	{
		line[len] = '\0';
		str = ft_strjoin(str, line);
		len = read(0, line, BLOCK_SIZE);
	}
	ft_strdel(&line);
	g_disp[flg->index](flg, al, str, len);
	flg->in = 0;
}

int		main(int argc, char **argv)
{
	t_flg	flg;
	t_alp	al;
	int		fd;

	fd = 0;
	if (argc < 2)
	{
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
		exit(1);
	}
	else
	{
		parse_alg(&flg, argv[1]);
		flag_init(&flg, argv, argc);
		alphabet_init(&al);
		if (flg.p || argc == 2)
			parse_stdin(&flg, &al);
		if (flg.s && argv[flg.i])
		{
			g_disp[flg.index](&flg, &al, argv[flg.i], 0);
			flg.s = 0;
			flg.i++;
		}
		else if (flg.s && !argv[flg.i])
		{
			ft_printf("%s: option requires an argument -- s\n", flg.alg);
			ft_printf("usage: ./ft_ssl [hash_function] [-pqr] ");
			ft_printf("[-s string] [files ...]\n");
			exit(1);
		}
		if (flg.fd)
		{
			while (flg.i < argc)
			{
				parse_file(&flg, &al, argv[flg.i], fd);
				flg.i++;
			}
		}
	}
	//while (1);
	return (0);
}
