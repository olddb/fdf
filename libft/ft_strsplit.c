/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 02:49:17 by vpailhe           #+#    #+#             */
/*   Updated: 2015/02/19 02:52:11 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int		ft_tablen(const char *s, char c)
{
	unsigned int	i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		nb++;
		while (s[i] == c)
			i++;
	}
	return (nb);
}

unsigned int		ft_wordlen(const char *s, char c)
{
	unsigned int	n;

	n = 0;
	while (s[n] != c && s[n] != '\0')
		n++;
	return (n);
}

char				*ft_strndup(const char *s1, size_t n)
{
	char			*s2;

	s2 = (char*)malloc(sizeof(*s1) * (n + 1));
	if (!s2)
		return (NULL);
	ft_strncpy(s2, s1, n);
	s2[n] = '\0';
	return (s2);
}

char				**ft_strsplit(const char *s, char c, int *p)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	len;

	i = 0;
	j = 0;
	len = ft_tablen(s, c);
	if (!(s) || !(tab = (char**)malloc(sizeof(*tab) * (len + 1))))
		return (NULL);
	tab[len] = NULL;
	*p = len;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		len = ft_wordlen(&s[i], c);
		tab[j] = ft_strndup(&s[i], len);
		j++;
		i += len;
		while (s[i] == c)
			i++;
	}
	return (tab);
}
