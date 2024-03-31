#include "../../inc/minishell.h"

void	env(t_data *data, int envi)
{
	int	i;

	i = 0;
	while (data->env[envi][i].key)
	{
		if (data->env[envi][i].exp)
			printf("%s=%s\n",
				data->env[envi][i].key, data->env[envi][i].value);
		i++;
	}
}
