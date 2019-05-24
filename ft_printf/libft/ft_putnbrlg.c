/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrlg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdenisov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:58:37 by kdenisov          #+#    #+#             */
/*   Updated: 2019/04/02 15:00:40 by kdenisov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrlg(long long int n)
{
	int						i;
	int						buffer[19];
	unsigned long long int	unb;

	i = 0;
	unb = n;
	if (n < 0)
	{
		unb = -unb;
		ft_putchar('-');
	}
	if (n == 0)
		ft_putchar('0');
	while (unb)
	{
		buffer[i] = unb % 10;
		unb = unb / 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		ft_putchar('0' + buffer[i]);
		i--;
	}
}
