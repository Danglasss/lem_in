/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:04:16 by dygouin           #+#    #+#             */
/*   Updated: 2020/01/31 21:17:45 by damboule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <math.h>
# include <limits.h>

# define t_size 52232
# define DEL 1
# define CLOSE -1
# define EMPTY 0
# define VISITED 1

/*
** Stocker tout et rien
*/

typedef struct       s_out
{
	int              nb_salle;
	int              ant_numb;
	unsigned long    salle_prev;
	unsigned long    index;
	int              truth;
	int              del[2];
	int              open;
	void             *out;
	struct s_out     *begin;
	struct s_out     *prev;
	struct s_out     *next;
}                    t_out;

/*
 ** Stocker les salles et leurs liens
 */

typedef struct       s_salle
{
	int				lenght;
	int				ascend;
	int             nb_salle;
	int             ant_numb;
	int             n_lem;
	int             free;
	unsigned long   salle_prev[2];
	char            *salle;
	t_out           *liens;
}                   t_salle;

/*
** Liste chainée des chemins eliminés par Bhandari
*/

typedef struct			s_banned
{
	unsigned long		room1;
	unsigned long		room2;
	struct s_banned		*begin;
	struct s_banned		*next;
}				t_banned;

/*
** Fait une snapshot, qui sauvegarde les lignes (de solution) et 
** les liens eliminés avant le reset des chemins.
*/

typedef struct			s_snapshot
{
	int				lines;
	t_banned		*banned;
}				t_snapshot;

/*
 ** Stocker les informations importantes (nombre de fourmies,
 ** nombre de chemins interessants, nom de la salle de fin/debut)
 */

typedef struct		s_stack
{
	int				finish;
	int				lenght;
	int				operation;
	int             result;
	int             fourmies;
	int             salle;
	int             ways;
	int             espoir;
	int             bhandari[2];
	unsigned long   index_end;
	unsigned long	index_start;
	char			*n_start;
	char			*n_end;
	t_banned		*banned;
}					t_stack;

void				permanant_delink(t_salle *room, t_stack *find, unsigned long index);
void				banned_cpy(t_banned **dst, unsigned long room1, unsigned long room2);
void				banned_add_tolist(t_banned **list, unsigned long room1, unsigned long room2);
void				init_algo(t_salle **room, t_stack **find, t_out **position, t_out **stack);
void				shot_init(t_snapshot **list);
void				repartition(t_salle *room, t_stack *find, unsigned long v_goals, int ants);
void				clean_map(t_salle *room, t_stack *find, t_out *index);
void				printpath(t_salle *room, t_stack *find);
void				path(t_salle *room, t_stack *find, unsigned long end, unsigned long salle_prev);
int					toplink(t_out *link, t_stack *find, t_salle *room, unsigned long index);
int					finish(t_salle *room, t_stack *find, t_out *index);
void				next(t_out **liens, t_out **stack);
void				ft_reset(t_salle *room, t_out *index);
void				ft_clean(t_salle *room, t_out *index);
void				clear(t_salle *room, t_stack *find, t_out *index);
void				transfert_true(t_salle *room, t_stack *find, unsigned long salle);
int					verify_colision(t_salle *room, unsigned long salle, t_stack *find);
void	            affichage(t_salle *room, t_stack *find);
int				    create_room(t_salle *room, char *hash, t_out **n_index);
int		            check_lformat(char *to_check, t_salle **rooms, int truth);
int		            check_rformat(char *to_check);
void	            print_list(t_out *p_list, t_salle *rooms);
void	            stack_room_init(t_stack **info, t_salle **rooms);
void                ft_initialisation(t_salle *rooms, t_stack *info);
void                nout_next(t_out **list, unsigned int count);
void		        ft_printread(t_out *read);
void				ft_print_out(t_out *store, t_salle *room);
int                 fonc(t_stack *find, t_salle *room);
unsigned long       t_hash(char *to_hash, t_salle *room);
int		            is_number(char *string, int check_if_int);
size_t	            ft_strtab(char **str);
int		            free_reset(void *ptr);
int		            is_int(char *isint);
int		            free_all(char **str, int truth);
long	            ft_atoi_check(char *str);
void				t_data(t_out **list, char **data);
int					len_out(t_out *list, int origin);
void				outn_prev(t_out **out, unsigned int n);
void				out_end(t_out **list);
t_out				*out_cpy(t_out *src);
void				out_init(t_out **list, int i);
void				out_add_tolist(t_out **list, char *data, int truth);
void				outfill_out(t_out **dst, t_out *src);
void                check_insert(t_out **reads, t_out **index, t_salle **rooms,
		t_stack *info);
void                leaks_out(t_out *leaks);
void                leaks_salle(t_salle *s, int a, t_out *i);
void		        cpy_length(t_out **dst, t_out *src, t_out **begin);
void                leaks_info(t_stack *info);
int		            bhandari(t_salle *room, t_stack *find, t_out *index);
void		      	algo(t_salle *room, t_stack *find, t_out *index, t_snapshot *current);
int		            bfs(t_salle *room, t_stack *find, unsigned long position,
		t_out **stack);
int		            ft_open(t_salle *room, t_out *liens, t_stack *find,
		unsigned long index);
int		            suplink(t_out *link, t_stack *find);
void	            blockchain(t_salle *room, unsigned long salle_prev,
		t_stack *find, unsigned long stack);
void	            next(t_out **liens, t_out **stack);
void	            print(t_out *stack, t_salle *room);
void	            findpath(t_salle *room, t_stack *find, unsigned long end);
void	            clear(t_salle *room, t_stack *find, t_out *index);
void	            print_lien(t_out *stack, t_salle *room);
void	            print_salle(t_out *stack, t_salle *room);
void				main_reset(t_salle *room, t_stack *find, t_out *index);
void				banned_init(t_banned **list, int i);

#endif
