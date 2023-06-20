#include "../../include/minishell/executor.h"

static char	ft_create_pipes(t_cmds *commands)
{
	int	fd[2];

	while (commands && commands->next)
	{
		if (pipe(fd) == -1)
			return (ft_perror(ERR_ERRNO, "pipe creation failed"),
				RETURN_FAILURE);
		commands->fd_out = fd[1];
		commands->next->fd_in = fd[0];
		commands = commands->next;
	}
	return (RETURN_SUCCESS);
}

static void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	ft_find_path(t_cmds *cmd, int i)
{
	char	**paths;
	char	*cmd_path;

	if (ft_strchr(cmd->argv[0], '/'))
	{
		if (access(cmd->argv[0], F_OK) == 0)
		{
			cmd->path = ft_strdup(cmd->argv[0]);
			return (RETURN_SUCCESS);
		}
		return (ERR_NO_FILE);
	}
	paths = ft_split(getenv("PATH"), ':');
	while (paths && paths[++i])
	{
		ft_asprintf(&cmd_path, "%s/%s", paths[i], cmd->argv[0]);
		if (cmd_path && access(cmd_path, F_OK) == 0)
		{
			cmd->path = cmd_path;
			return (ft_free_paths(paths), RETURN_SUCCESS);
		}
		free(cmd_path);
	}
	return (ft_free_paths(paths), ERR_CMD_NOT_FOUND);
}

int	ft_execute(int status, t_cmds *commands)
{
	t_cmds	*cmd;
	char	err;

	if (!commands || ft_create_pipes(commands) == RETURN_FAILURE)
		return (ft_free_cmds(commands), RETURN_FAILURE);
	if (verbose)
	{
		print_cmds(commands);
		printf("\e[1;33mOUTPUT\e[0m\n");
	}
	cmd = commands;
	while (cmd && g_ctrlc == false)
	{
		ft_check_builtin(cmd);
		if (cmd->builtin != B_NO && cmd->builtin != B_ECHO)
			status = ft_run_builtin(cmd, commands);
		else if (cmd->builtin == B_ECHO)
			status = ft_create_child(status, cmd);
		else
		{
			err = ft_find_path(cmd, -1);
			if (err)
				status = ft_perror(err, cmd->argv[0]);
			else
				status = ft_create_child(status, cmd);
		}
		cmd = cmd->next;
	}
	return (ft_free_cmds(commands), status);
}
