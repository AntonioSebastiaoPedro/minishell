/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansebast <ansebast@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:37:32 by ansebast          #+#    #+#             */
/*   Updated: 2024/11/05 08:34:47 by ansebast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_setenv(const char *name, const char *value, int overwrite) {
    if (!name || !value) {
        return -1;
    }

    char *existing_value = getenv(name);

    if (existing_value && !overwrite) {
        return 0;
    }

    size_t length = strlen(name) + strlen(value) + 2;
    char *env = malloc(length);
    if (!env) {
        return -1;
    }

    sprintf(env, "%s=%s", name, value);

    if (putenv(env) != 0) {
        free(env);
        return -1;
    }
    free(env);
    return 0;
}
