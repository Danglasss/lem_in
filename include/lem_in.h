/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:04:16 by dygouin           #+#    #+#             */
/*   Updated: 2020/02/11 18:31:31 by damboule         ###   ########.fr       */
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

typedef struct		s_cases
{
	unsigned long	index;
	struct s_cases	*begin;
	struct s_cases	*next;
}					t_cases;

typedef	struct		s_path
{
	t_cases			*cases;
	int				lines;
	int				ants;
	int				length;
}					t_path;

/*
 ** Stocker les informations importantes (nombre de fourmies,
 ** nombre de chemins interessants, nom de la salle de fin/debut)
 */

typedef struct		s_stack
{
	int				counter_del;
	int				finish;
	int				lenght;
	int				truth;
	int             fourmies;
	int             salle;
	int             ways;
	int             error;
	int             bhandari[2];
	unsigned long   index_end;
	unsigned long	index_start;
	char			*n_start;
	char			*n_end;
}					t_stack;

void	p(t_salle *room, t_stack *find, t_path *current);
int					same_path(t_salle *room, t_stack *find, unsigned long index, unsigned long value);
int					stop_up(t_out *link, t_stack *find, t_salle *room, unsigned long index);
void				delete_link(t_out **liens, t_salle *room, unsigned long salle);
int					repart_eval(t_salle *room, t_stack *find, t_out *link, t_path *current);
void				path_cpy(t_path **best, t_path *curr, int len);
void				clean_current(t_path **current, int len);
void 				clean_cases(t_cases **room);
void				cases_add_tolist(t_cases **list, unsigned long index);
void				cases_init(t_cases **list, int i);
void				path_init(t_path **path, t_salle *room, t_stack *find);
void				ft_clean_end(t_salle *room, t_stack *find);
void				permanant_delink(t_salle *room, t_stack *find, unsigned long index);
void				init_algo(t_salle **room, t_stack **find, t_out **position, t_out **stack);
void				repartition(t_salle *room, t_stack *find, unsigned long v_goals, int ants);
void				clean_map(t_salle *room, t_stack *find, t_out *index);
void				printpath(t_salle *room, t_stack *find, t_path *current);
void				path(t_salle *room, t_stack *find, unsigned long salle_prev, t_cases *current);
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
void                leaks_out(t_out *leaks, int i);
void                leaks_salle(t_salle *s, int a, t_out *i);
void		        cpy_length(t_out **dst, t_out *src, t_out **begin);
void                leaks_info(t_stack *info);
void		        bhandari(t_salle *room, t_stack *find, t_out *index, t_path *best_shot);
void		      	algo(t_salle *room, t_stack *find, t_out *index, t_path *current);
int		            bfs(t_salle *room, t_stack *find, unsigned long position,
		t_out **stack);
int		            ft_open(t_salle *room, t_out *liens, t_stack *find,
		unsigned long index);
int		            suplink(t_out *link, t_stack *find);
void	            blockchain(t_salle *room, unsigned long salle_prev,
		t_stack *find, unsigned long stack);
void	            next(t_out **liens, t_out **stack);
void	            print(t_out *stack, t_salle *room);
void	            findpath(t_salle *room, t_stack *find, unsigned long end, t_path *current);
void	            clear(t_salle *room, t_stack *find, t_out *index);
void	            print_lien(t_out *stack, t_salle *room);
void	            print_salle(t_out *stack, t_salle *room);
void				main_reset(t_salle *room, t_stack *find, t_out *index, t_path *current);
void   				leaks_path(t_path *path, int len);
void				free_all_l(t_out **list);

#endif
