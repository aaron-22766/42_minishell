#include "../../include/minishell/parser.h"

t_cmds	*ft_free_cmd(t_cmds *cmd)
{
	t_cmds	*next;
	size_t	i;

	free(cmd->path);
	i = -1;
	while (cmd->argv && cmd->argv[++i])
		free(cmd->argv[i]);
	free(cmd->argv);
	ft_free_tokens(cmd->io_red);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	next = cmd->next;
	free(cmd);
	return (next);
}

void	ft_free_commands(t_cmds *cmd)
{
	while (cmd)
		cmd = ft_free_cmd(cmd);
}

ssize_t	ft_setchar(char *str, char c, ssize_t index)
{
	if (c == '/' && index < 0)
		return (ft_strlen(str));
	if (!str || index < 0 || index > (ssize_t)ft_strlen(str))
		return (-1);
	str[index] = c;
	return (index);
}

void	print_cmds(t_cmds *commands)
{
	size_t	i;

	printf("\e[1;33mCOMMANDS\e[0m\n");
	if (!commands)
		printf("No commands\n");
	while (commands)
	{
		printf("PATH: %s\n", commands->path);
		printf("ARGS:");
		i = -1;
		while (commands->argv && commands->argv[++i])
			printf("[%s]", commands->argv[i]);
		printf("\nREDIRECTIONS:\n");
		print_tokens(commands->io_red, NULL);
		printf("fd_in: %d\nfd_out: %d\n", commands->fd_in, commands->fd_out);
		commands = commands->next;
		if (commands)
			printf("\e[0;33m↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓\e[0m\n");
	}
}
