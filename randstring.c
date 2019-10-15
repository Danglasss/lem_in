/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randstring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: affect <affect@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 11:01:56 by affect            #+#    #+#             */
/*   Updated: 2019/08/03 14:08:44 by affect           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char    *randstring(unsigned int len) {
    char                *nr_string;
    unsigned int        i;
    char                string_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghij\
klhmnopqrstuvwxyz 0123456789\\()_-=+><,./?'|[]{}!@#$%^&*";
    
    if (len == 0 || !(nr_string = (char *)malloc(sizeof(char) * len + 1)))
        return (NULL);
    srand(time(NULL) * len);
    i = 0;
    while (i < len) {
        nr_string[i] =  string_chars[(rand() + i) % (sizeof(string_chars) - 1)];
        i++;
    }
    nr_string[i] = '\0';
    return (nr_string);
}
