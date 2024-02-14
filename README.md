<h1 align="center">
	<p>
	minishell
	</p>
	<img src="https://github.com/ayogun/42-project-badges/blob/main/badges/minishelle.png">
</h1>

<p align="center">
	<b><i>As beautiful as a shell</i></b><br><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/aaron-22766/42_minishell?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/aaron-22766/42_minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/aaron-22766/42_minishell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/aaron-22766/42_minishell?color=green" />
</p>

---

## 🗣 About

This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.

This is the first team project of the 42 Cursus and I teamed up with [Raffael](https://github.com/Raffael-Passion).

## 🛠 Usage

```shell
$> make
$> ./minishell [-v optional]
▶ $> # you are now in the minishell prompt
```

## 💬 Description

Here's a rough description about what our minishell does.

### Init shell

* allocate and copy the `extern char **environ` because we need to alter it
* OLDPWD is added if it doesn't exist
* PWD is set to the current directory
* SHLVL gets incremented
* SHELL gets set to the path of our minishell executable

### Environment

* as we are not allowed to use the functions, we wrote our own implementation for `putenv`, `setenv` and `unsetenv`

### Terminal

* for ignoring the `^C` when ctrl-C is pressed, we remove `ECHOCTL` from the terminal attributes by using the functions `tcgetattr` and `tcsetattr`

### following is the main loop for readline

### Prompt

* prompt is generated from the `PS1` environment variable, if it is set
* it follows the bash rules for expansion
* `[`, `]`, `a`, `e`, `n`, `r`, `\`, `s`, `w`, `W`, `u`, `h`, `H` are supported escape characters that get replaces if it is preceeded by a backslash
* user, hostname and working directory are the most useful and require the corresponding environment variables to be set
* the prompt also starts with a colored `▶` as a status indicator, it's grey by default, green on sucess and red if the execution failed

### Readline

* we call `line = readline(prompt);`
* if the line is NULL and the readline variable `rl_eor_found` is true, it means that ctrl-D was pressed and the shell should exit (after freeing everything or course)
* then we add the line to the history if it isn't empty
* we check the line for only whitespace characters, in which case we don't need to do anything (loop starts over) and the prompt status should turn grey

### Lexer

* the line gets passed to the lexer, which splits it up into a linked list of tokens
```c
typedef struct s_tokens
{
    char id;
    char *content;
    struct s_tokens *next;
}   t_tokens;
```
* the id specifies what the `content` string actually is, that makes it easy for the parser to loop over it without needing to do strcmp all the time
* it's also designed as a bitmap to have the two categories `WORD` and `OPERATOR`
```c
0b00000001 WORD
0b00000101 IN_FILE (the word after a IN_RED)
0b00001001 OUT_FILE (the word after a OUT_RED)
0b00010001 HEREDOC_EOF (the word after a HEREDOC)
0b00100001 OUT_A_FILE (the word after a OUT_A_RED)
0b01000001 COMMAND (the first word between PIPEs that is not one of the above)
0b00000010 OPERATOR
0b00000110 IN_RED (<)
0b00001010 OUT_RED (>)
0b00010010 HEREDOC (<<)
0b00100010 OUT_A_RED (>>)
0b01000010 PIPE (|)
```
* the lexer also needs to detect single and double quotes correctly to form the words and not to interpret meta-characters in-between them
* if there are unclosed quotes, minishell doesn't do the same as bash and will just print a syntax error

### Expander

* the expander is integrated in the parser but the expansion happens before the main parser job anyway
* all the tokens are analyzed and `WORD`s that are not `HEREDOC_EOF` are expanded
* `~` is expanded to `HOME`
* `~+` with optional path afterwards is expanded to `PWD`
* `~-` with optional path afterwards is expanded to `OLDPWD`
* these tilde expansions are also applied to assignments if the tilde is preceeded immediately by the `=`
* the following expansions are also used for the heredoc
* `$` must be followed by a valid variable name - first digit must be alpha or underscore, following alnum or a number of allowed characters
* also quotes and backslashes need to be handled correctly - var name is only until the first quote unless it's escaped by backlash (simplified example)
* if a valid name is found, we look if there is a value (`getenv`) in the environment and it gets replaced if there is one
* after this escaping backslashes are removed (`\\` is just `\`)
* all the time quotes are really important to know what gets expanded - nothing between single quotes

### Parser

* the parser receives the tokens and sets up a linked list of commands
```c
typedef struct s_cmds
{
    char *path;
    char **argv;
    t_tokens *io_red;
    int fd_in;
    int fd_out;
    char builtin;
    struct s_cmds *next;
}   t_cmds;
```
* after the expansion of the tokens, the quotes are removed from the words where applicable
* `path` is created later
* `argv` is a string array containing the arguments that need to be passed to `execve`
* `io_red` contains only the redirection tokens in order for the executor to set up the redirections
* `fd_in` and `fd_out` are file descriptors that are set later (default to stdin and stdout) for the executor to set up the redirections
* `builtin` is set later (default `B_NO`) for the executor to know if which builtin it is

### Executor

#### Builtin

* we check if `argv[0]` is one of our implemented builtins, for this we made a bitmap
```c
0b00000000 B_NO
0b00000001 B_PARENT
0b00000011 B_EXIT
0b00000101 B_CD
0b00001001 B_EXPORT
0b00010001 B_UNSET
0b00000010 B_PWD
0b00000100 B_ECHO
0b00001000 B_ENV
```
* this makes it easy to check where the builtin needs to run (builtin & `B_PARENT` → should alter the current/parent process, no child needed)
* `EXPORT`, `EXIT`, `CD` and `UNSET` only work if it's a sinle command, that's why we check for this in the beginning and run them if that's the case

#### Redirections

* loops over `io_red` tokens and sets `fd_in` and `fd_out` accordingly
* `OUT_FILE` and `OUT_A_FILE` open/create a file in O_WRONLY with the file name in the `content` of the token an the right permissions
* `IN_FILE` opens the file in O_RDONLY
* `HEREDOC` creates a pipe for an "invisible" temporary file, has another readline loop where it reads and expands the line and writes it to the pipe - `fd_in` is set to the pipes read end

#### Pipeline

* this is a recursive function (split up into multiple for norminette) that creates all the child processes with the correct pipes
* if the command is a parent builtin, it just gets ignored
* the child process then used `dup` to redirect the input and output to/from file or pipe
* if it's a child builtin, it is executed
* now we find the absolute path to the executable using the `PATH` variable
* we call `execve` with `path`, `argv` and `environ`
* the recursiveness of this function creates all the child processes simultaneously (previous consequtive method is another branch)
* in the meantime the parent process waits for all childs to exit and afterwards all commands are freed

### Signals

* during the entire parent process ctrl-\ is ignored
* ctrl-C will always set a global variable to true, which quits the current processing and returns to readline
* during readline ctrl-C needs some more functions so that we get a new line because readline doesn't return
* the heredoc also has a special handler for readline
* ctrl-\ isn't handled but it should inside heredocs which is an oversight on our part

### Builtins

#### exit

* exits the shell with the status in the argument or the current status if none is specified
* also needs a numeric argument for the status otherwise it will error

#### cd

* changes the current directory to the first argument provided
* can be relative or absolute path
* `--` changes to `HOME`
* `-` changes to `OLDPWD`
* `PWD` and `OLDPWD` are set accordingly

#### export

* with an argument it needs a valid identifier followed by an optional `=` and value
* creates or changes the value of an existing environment variable
* if no argument is provided it will print the environment variables in a weird format

#### unset

* with a valid identifier as argument it unsets/deletes the environment variable
* otherwise it shows an error

#### pwd

* prints the current working directory to the stdout

#### echo

* writes all the arguments to stdout followed by a newline
* if the option `-n` is specified, no newline is added afterwards
* some interesting differences are between "echo" in just lowercase and any other case version, as the latter would also accept multiple `-n` with as many "n" as we want

#### env

* prints the current environment variables to the stdout


  
