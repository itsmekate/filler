/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kprasol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:14:38 by kprasol           #+#    #+#             */
/*   Updated: 2018/04/16 17:18:27 by kprasol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>

typedef	struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef	struct	s_board
{
	int			col;
	int			row;
	int			player;
	char		**board;
}				t_board;

typedef	struct	s_piece
{
	int			col;
	int			row;
	int			cut_top;
	int			cut_left;
	char		**piece;
}				t_piece;

typedef struct	s_norm
{
	t_board	b;
	t_piece	p;
	char	en;
	char	pl;
	int		cross;
}				t_norm;

void			ft_set_solution(t_coord	*solution);
int				abs(int n);
int				test(t_board *mb, t_piece *mp, t_coord *r);
int				len(t_coord res, t_board *mb);
void			ft_piece(struct s_piece *my_piece);
void			ft_write_board(t_board *my_board, int check);
void			ft_write_piece(struct s_piece *mp);
t_coord			ft_place(t_board *mb, t_piece *mp);
void			ft_cut_left_even_more(struct s_piece *mp, t_coord	n);
void			ft_cut_left(struct s_piece *my_piece);
t_coord			ft_place(t_board *my_board, struct s_piece *my_piece);
#endif
