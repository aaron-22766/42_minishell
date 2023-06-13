

char	*ft_find_path(char *command)
{
	extern char	**environ;
	char		**paths;
	char		*tmp;
	char		*cmd_path;
	int			i;

	i = 0;
	while (environ[i++])
		if (ft_strnstr(environ[i], "PATH", 4) == 0)
			paths = ft_split(environ[i] + 5, ':');
	i = 0;
	while (paths[i++])
	{
		tmp = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(tmp, command);
		free(tmp);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
	}
	ft_free_paths(paths);
	return (0);
}

void	ft_free_paths(char **paths)
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

int	ft_check_builtin(t_cmds *command)
{
	char	*cmd;

	cmd = ft_str_tolower(command->argv[0]);
	if (ft_strcmp("echo", cmd) == 0)
		ft_echo(command);
	else if (ft_strcmp("cd", cmd) == 0)
		ft_cd(command);
	else if (ft_strcmp("pwd", cmd) == 0)
		ft_pwd(command);
	else if (ft_strcmp("export", cmd) == 0)
		ft_export(command);
	else if (ft_strcmp("unset", cmd) == 0)
		ft_unset(command);
	else if (ft_strcmp("env", cmd) == 0)
		ft_env(command);
	return (free(cmd), 0);
}

void	ft_execute_child(t_cmds *command)
{
	char	*cmd;

	signal(SIGINT, ft_sig_handler);
	if (ft_install_redirections(command) == RETURN_FAILURE)
		exit(EXIT_FAILURE);
	command->path = ft_find_path(command->argv[0]);
	if (!command->path)
		exit(EXIT_FAILURE);
	if (g_ctrlc == true)
		exit(130);
	ft_check_builtin(command);
	execve(command->path, command->argv, NULL);
	ft_perror(ERR_ERRNO, "failed to execute command");
	exit(EXIT_FAILURE);
}
