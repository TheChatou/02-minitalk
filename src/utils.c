/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:01:42 by fcoullou          #+#    #+#             */
/*   Updated: 2024/03/27 14:02:07 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <signal.h>
#include <sys/ucontext.h>
#include <sys/types.h>

void	clean_exit(char *str)
{
	if (!ft_strncmp(str, "exit", 5))
	{
		free(str);
		exit(0);
	}
}

char	*ft_strjoinchar(char const *str, char c)
{
	char	*dest;
	size_t	len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	dest = (char *)malloc((len + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	if (str)
		ft_memcpy(dest, str, len);
	if (c)
		ft_memcpy(dest + len, (const void *)&c, 1);
	dest[len + 1] = '\0';
	return (dest);
}
