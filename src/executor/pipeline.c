#include "../../include/minishell/executor.h"

void	ft_close_fds(int pipe_in, int fd[2], char condition)
{
	if (pipe_in != -1)
		close(pipe_in);
	if (condition)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

static char	ft_skip_cmd(t_cmds *next, char ret)
{
	if (next)
		return (ft_pipeline(next, -1));
	return (ret);
}

static int	ft_parent(t_cmds *cmd, int fd[2], pid_t child_pid)
{
	int	wait_status;
	int	status;

	if (cmd->next)
	{
		close(fd[1]);
		status = ft_pipeline(cmd->next, fd[0]);
	}
	if (waitpid(child_pid, &wait_status, WUNTRACED) == -1)
		return (ft_perror(ERR_ERRNO, "waitpid"));
	if (!cmd->next)
		status = WEXITSTATUS(wait_status);
	return (status);
}

int	ft_pipeline(t_cmds *cmd, int pipe_in)
{
	pid_t	pid;
	int		fd[2];

	if (g_ctrlc == true)
		return (ft_close_fds(pipe_in, fd, false), 130);
	ft_check_builtin(cmd);
	if (!cmd->argv)
		return (ft_close_fds(pipe_in, fd, false),
			ft_skip_cmd(cmd->next, RETURN_FAILURE));
	if ((cmd->builtin & B_PARENT)
		&& !(cmd->builtin == B_EXPORT && !cmd->argv[1]))
		return (ft_close_fds(pipe_in, fd, false),
			ft_skip_cmd(cmd->next, RETURN_SUCCESS));
	if (cmd->next && pipe(fd) == -1)
		return (ft_close_fds(pipe_in, fd, false),
			ft_perror(ERR_ERRNO, "pipe"), RETURN_FAILURE);
	pid = fork();
	if (pid < 0)
		return (ft_close_fds(pipe_in, fd, !!cmd->next),
			ft_perror(ERR_ERRNO, "fork"), RETURN_FAILURE);
	if (pid == 0)
		ft_child(cmd, fd, pipe_in);
	return (ft_close_fds(pipe_in, fd, false), ft_parent(cmd, fd, pid));
}
