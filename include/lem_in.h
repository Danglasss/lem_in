/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damboule <damboule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:04:16 by nabboufe          #+#    #+#             */
/*   Updated: 2019/10/18 17:18:01 by damboule         ###   ########.fr       */
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

# define t_size 522321  

/*
** Stocker tout et rien 
*/

typedef struct       s_out
{
    unsigned long    touch;
    int              truth; 
    void             *out;
    struct s_out     *begin;
    struct s_out     *prev;
    struct s_out     *next;
}                    t_out;

/*
** Stocker les chemins
*/

typedef struct       s_pos
{
    int              id;
    int              colle;
    int              fourmies;
    int              salle;
    int              instruction;
    int              finish;
    t_out            *ways;
    t_out            *colision;
    struct s_pos     *begin;
    struct s_pos     *next;
    struct s_pos     *prev;
}                    t_pos;

/*
** Stocker les salles et leurs liens
*/

typedef struct       s_salle
{
    int             path;
    int             n_lem;
    char            *salle;
    t_out           *collision;
    t_out           *liens;
}                   t_salle;

/*
** Stocker les informations importantes (nombre de fourmies,
** nombre de chemins interessants, nom de la salle de fin/debut)
*/

typedef struct      s_stack
{
    int             lenght;
    int             operation;
    int             result;
    int             fourmies;
    int             salle;
    int             ways;
    int             espoir;
    unsigned long   index_end;
    unsigned long   index_start;
    char            *n_start;
    char            *n_end;
}                   t_stack;

typedef struct      s_struct
{
int                 instruct;
int                 salle;
int                 fourmies;
int                 nb;
}                   t_struct;

void	            ft_copy(t_pos *pos, t_stack *find, t_pos *path);
int		            occur(int colle, t_pos *path, t_pos *pos);
int			        ft_add_way(t_pos **pos, int colle);
void	            ft_set_reset(t_salle *room, t_stack *find, t_pos *pos, t_pos *path);
void		        ft_bfs(t_salle *room, t_stack *find, t_pos *pos, t_pos *path);
void		        ft_reset_repertition(t_pos *pos);
void		        ft_initia(t_pos *path, t_salle *room);
void		        ft_room_colision(t_pos *path, t_salle *room);
int				    create_room(t_salle *room, char *hash, t_out **n_index);
int		            check_lformat(char *to_check, t_salle **rooms, int truth);
int		            check_rformat(char *to_check);
void	            ft_colision(/*t_out *col, */t_pos *path, t_salle *room);
int			        ft_max(t_pos *path);
int                 f_equal(t_pos *path, int fourmie);
int		            f_repartition(t_pos *path);
void	            print_list(t_out *p_list, t_salle *rooms);
void                init_leak(t_out **reads, t_out **index, t_pos **path, t_pos **pos);
void                stack_room_init(t_stack **info, t_salle **rooms);
void                ft_initialisation(t_salle *rooms, t_stack *info);
void                nout_next(t_out **list, unsigned int count);
void                npos_next(t_pos **list, unsigned int count);
void	        	t_end(t_stack *info, t_salle *room, t_pos *path);
void		        ft_printread(t_out *read);
void                pos_istrue(t_pos *pos);
void	        	ft_print_out(t_out *store, t_salle *room);
int         		ft_edmonds(t_salle *room, t_stack *find, t_pos *pos,
                        t_pos *path);
void		        print_allpos(t_pos *pos, t_salle *room);
void                inti(t_struct *way, t_stack *find, int max);
int                 fonc(t_stack *find, t_salle *room);
int		            ft_calculpath(t_struct *way, t_stack *find, int max_path);
unsigned long       t_hash(char *to_hash, t_salle *room);
int		            is_number(char *string, int check_if_int);
size_t	            ft_strtab(char **str);
int    	            free_reset(void *ptr);
int		            is_int(char *isint);
int 	            free_all(char **str, int truth);
long	            ft_atoi_check(char *str);
void    			pos_add_tolist(t_pos **list, t_out *data, int truth);
void    			t_data(t_out **list, char **data);
void    			pos_init(t_pos **list, int i);
int     			len_pos(t_pos *list, int origin);
int     			len_out(t_out *list, int origin);
void    			posn_prev(t_pos **pos, unsigned int n);
void    			outn_prev(t_out **out, unsigned int n);
void    			out_end(t_out **list);
void    			pos_end(t_pos **list);
t_out   			*out_cpy(t_out *src);
void    			out_init(t_out **list, int i);
void    			out_add_tolist(t_out **list, char *data, int truth);
void    			outfill_out(t_out **dst, t_out *src);
void                check_insert(t_out **reads, t_out **index, t_salle **rooms,
                        t_stack *info);
void                leaks_out(t_out *leaks);
void                leaks_pos(t_pos *leaks);
void                leaks_salle(t_salle *s, int a, t_out *i);
void		        cpy_length(t_out **dst, t_out *src, unsigned long max);
void		        ft_index(t_pos *pos, long long *prev_index, long long *t_index, int *count);
void		        ft_main_bfs(t_salle *room, t_stack *find, t_pos *pos, t_pos *path);
void                leaks_struct(t_struct *way, int max);
void                leaks_info(t_stack *info);
void		        ft_take_path(t_pos *path);
void		        ft_begin(t_stack *find, t_pos *pos, t_salle *room);



#endif