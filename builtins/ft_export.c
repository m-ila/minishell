/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 11:59:40 by chourael          #+#    #+#             */
/*   Updated: 2024/01/10 13:34:45 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//la cmd export prend 1 seul argument, l'arg doit etre dans cette forme
//VARNAME=VALUE ou VARNAME="VALUE VALUE" sinon export ne fait rien
//fonctionne meme si VARNAME n'est pas en maj
//si une variable existe déjà export va la modifier et si elle n'existe
// pas elle vas la créé
// exemple export yeah=yeahyeah la variable yeah n'existe pas alors yeah
// vas etre créé et etre = a yeahyeah
//export yeah=nono la variable existe déja donc on export change juste
// la valeur de la variable donc yeahyeah par nono
//search for the variable inside env and replace it with the arg
// (assuming arg is correct)

static char	**ft_replaceit(char **env, char *arg, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
		{
			free(env[i]);
			env[i] = malloc(sizeof(char) * (ft_strlen(arg) + 1));
			ft_strlcpy(env[i], arg, (ft_strlen(arg) + 1));
		}
		i++;
	}
	return (env);
}

//itterate env untile NULL and replace NULL by the new
//variable and it's value (assuming arg is correct)
static char	**ft_addit(char **env, char *arg)
{
	int		i;
	char	**envcpy;

	i = 0;
	envcpy = malloc(sizeof(char *) * (ft_len(env) + 2));
	ft_cpymalloc(envcpy, env);
	while (env[i] != NULL)
	{
		ft_strlcpy(envcpy[i], env[i], (ft_strlen(env[i]) + 2));
		i++;
	}
	envcpy[i] = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	ft_strlcpy(envcpy[i], arg, (ft_strlen(arg) + 1));
	envcpy[i + 1] = NULL;
	ft_freeenv(env);
	return (envcpy);
}

//take what is befor the = to make the variable name
//(exemple if arg is THEBEST=chourael,marnianne then variable will be "THEBEST")
static char	*ft_get_var(char *arg)
{
	char	*variable;
	int		i;

	i = 0;
	while (arg[i] != '=')
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (arg[i] != '=')
	{
		variable[i] = arg[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

static int	search(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	**ft_export(char **env, char *arg)
{
	char	*variable;

	variable = ft_get_var(arg);
	if (search(env, variable) == 0)
	{
		env = ft_addit(env, arg);
		free(variable);
		return (env);
	}
	else if (search(env, variable) == 1)
	{
		env = ft_replaceit(env, arg, variable);
		free(variable);
		return (env);
	}
	free(variable);
	return (env);
}
