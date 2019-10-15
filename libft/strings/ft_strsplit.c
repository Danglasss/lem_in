/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:50:15 by damboule          #+#    #+#             */
/*   Updated: 2019/07/24 13:10:24 by nabboufe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

static int	ft_count_word(char const *s, char c)
{
	int i;
	int	a;

	i = 0;
	a = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			a++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (a);
}

static int	ft_count_letter(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		a;

	if (s == NULL)
		return (NULL);
	tab = (char**)malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	a = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			tab[a] = ft_strsub(s, i, ft_count_letter(s, c, i));
			i += ft_count_letter(s, c, i);
			a++;
		}
	}
	tab[a] = 0;
	return (tab);
}
