/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chourael <chourael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:19:40 by chourael          #+#    #+#             */
/*   Updated: 2024/01/07 10:51:34 by chourael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../Marianne_libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

//echo.c
void	ft_echo(char *str);

//cd.c
int		ft_cd(char *str);

//pwd.c
void	ft_pwd(char **env);

//export.c
char	**ft_export(char **env, char *arg);

//unset.c
char	**ft_unset(char **env, char **arg, int i, int j);
int		ft_malloccpy(char **envcpy, char **env, char **arg);
int		ft_len(char **env);

//env.c
void	ft_env(char **env);
void	ft_freeenv(char **env);

//malloc.c
int		ft_cpymalloc(char **envcpy, char **env);

#endif