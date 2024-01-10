/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbruyant <mbruyant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:16:51 by chourael          #+#    #+#             */
/*   Updated: 2024/01/10 13:35:00 by mbruyant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	ft_checkspecial(char *arg)
{
	if (ft_strncmp(arg, "SHLVL", 5) == 0)
	{
		// printf("here \n");
		return (1);
	}
	return (0);
}

int	ft_malloccpy(char **envcpy, char **env, char **arg)
{
	int	i;
	int	o;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		o = 0;
		while (arg[o])
		{
			if (ft_strncmp(env[i], arg[o], ft_strlen(arg[o])) == 0)
			{
				// printf("env[%d] = %s \n", i, env[i]);
				if (ft_checkspecial(arg[o]) == 0)
					i++;
			}
			o++;
		}
		if (env[i] != NULL)
			envcpy[j] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		else if (env[i] == NULL)
			break ;
		if (envcpy[j] == NULL)
			return (-1);
		j++;
		i++;
	}
	return (0);
}

int	ft_special(char *env, char *arg, char **envcpy, int j)
{
	int	i;

	if (ft_strncmp(arg, "SHLVL", 5) == 0)
	{
		i = 0;
		while (env[i])
		{
			if (i > 0 && env[i - 1] == '=')
				envcpy[j][i] = '0';
			else
				envcpy[j][i] = env[i];
			i++;
		}
		envcpy[j][i] = '\0';
		return (1);
	}
	return (0);
}

char	**ft_unset(char **env, char **arg, int i, int j)
{
	int		o;
	char	**envcpy;

	envcpy = malloc(sizeof(char *) * (ft_len(env) + 1));
	ft_malloccpy(envcpy, env, arg);
	while (env[i])
	{
		o = 0;
		while (arg[o])
		{
			if (ft_strncmp(env[i], arg[o], ft_strlen(arg[o])) == 0)
			{
				if (ft_special(env[i], arg[o], envcpy, j) == 1)
				{
					// printf("envcy[%d] = %s \n", i, envcpy[j]);
					j++;
				}
				i++;
			}
			o++;
		}
		if (env[i] == NULL)
			break ;
		ft_strlcpy(envcpy[j], env[i], (ft_strlen(env[i]) + 1));
		i++;
		j++;
	}
	envcpy[j] = NULL;
	ft_freeenv(env);
	return (envcpy);
}
