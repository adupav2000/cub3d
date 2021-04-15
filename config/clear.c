/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pavi <adu-pavi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 13:37:58 by adu-pavi          #+#    #+#             */
/*   Updated: 2021/04/15 17:50:20 by adu-pavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	exit_error(t_game *game, char *message)
{
	clear_all_variables(game);
	if (message[0] == 0)
	{
		perror("Error ");
	}
	else
	{
		ft_putstr_fd("Error : ", 1);
		ft_putstr_fd(message, 1);
		ft_putstr_fd("\n", 1);
	}
	return (-1);
}

int	exit_success(t_game *game)
{
	clear_all_variables(game);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
