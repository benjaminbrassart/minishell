# Allowed external functions

<details>
<summary>Expand</summary>

- [readline](https://tiswww.case.edu/php/chet/readline/readline.html#SEC24)
- [rl_clear_history](https://tiswww.case.edu/php/chet/readline/history.html#SEC11)
- [rl_on_new_line](https://tiswww.case.edu/php/chet/readline/readline.html#SEC35)
- [rl_replace_line](https://tiswww.case.edu/php/chet/readline/readline.html#SEC39)
- [rl_redisplay](https://tiswww.case.edu/php/chet/readline/readline.html#SEC35)
- [add_history](https://tiswww.case.edu/php/chet/readline/history.html#SEC11)
- [printf](https://man7.org/linux/man-pages/man3/printf.3.html)
- [malloc](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [free](https://man7.org/linux/man-pages/man3/free.3.html)
- [write](https://man7.org/linux/man-pages/man2/write.2.html)
- [access](https://man7.org/linux/man-pages/man2/access.2.html)
- [open](https://man7.org/linux/man-pages/man2/open.2.html)
- [read](https://man7.org/linux/man-pages/man2/read.2.html)
- [close](https://man7.org/linux/man-pages/man2/close.2.html)
- [fork](https://man7.org/linux/man-pages/man2/fork.2.html)
- [wait](https://man7.org/linux/man-pages/man2/wait.2.html)
- [waitpid](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [wait3](https://man7.org/linux/man-pages/man2/wait3.2.html)
- [wait4](https://man7.org/linux/man-pages/man2/wait4.2.html)
- [signal](https://man7.org/linux/man-pages/man2/signal.2.html)
- [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [kill](https://man7.org/linux/man-pages/man2/kill.2.html)
- [exit](https://man7.org/linux/man-pages/man2/exit.2.html)
- [getcwd](https://man7.org/linux/man-pages/man2/getcwd.2.html)
- [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html)
- [stat](https://man7.org/linux/man-pages/man2/stat.2.html)
- [lstat](https://man7.org/linux/man-pages/man2/lstat.2.html)
- [fstat](https://man7.org/linux/man-pages/man2/fstat.2.html)
- [unlink](https://man7.org/linux/man-pages/man2/unlink.2.html)
- [execve](https://man7.org/linux/man-pages/man2/execve.2.html)
- [dup](https://man7.org/linux/man-pages/man2/dup.2.html)
- [dup2](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [opendir](https://man7.org/linux/man-pages/man3/opendir.3.html)
- [readdir](https://man7.org/linux/man-pages/man2/readdir.2.html)
- [closedir](https://man7.org/linux/man-pages/man3/closedir.3.html)
- [strerror](https://man7.org/linux/man-pages/man3/strerror.3.html)
- [perror](https://man7.org/linux/man-pages/man3/perror.3.html)
- [isatty](https://man7.org/linux/man-pages/man3/isatty.3.html)
- [ttyname](https://man7.org/linux/man-pages/man3/ttyname.3.html)
- [ttyslot](https://man7.org/linux/man-pages/man3/ttyslot.3.html)
- [ioctl](https://man7.org/linux/man-pages/man2/ioctl.2.html)
- [getenv](https://man7.org/linux/man-pages/man3/getenv.3.html)
- [tcsetattr](https://man7.org/linux/man-pages/man3/tcsetattr.3.html)
- [tcgetattr](https://man7.org/linux/man-pages/man3/tcgetattr.3.html)
- [tgetent](https://man7.org/linux/man-pages/man3/curs_termcap.3x.html)
- [tgetflag](https://man7.org/linux/man-pages/man3/curs_termcap.3x.html)
- [tgetnum](https://man7.org/linux/man-pages/man3/curs_termcap.3x.html)
- [tgetstr](https://man7.org/linux/man-pages/man3/curs_termcap.3x.html)
- [tgoto](https://man7.org/linux/man-pages/man3/curs_termcap.3x.html)
- [tputs](https://man7.org/linux/man-pages/man3/curs_termcap.3x.html)
</details>

# Tips

When creating forks and pipes, if the first executable is a builtin, bash executes it in its main process.
If a builtin is not the first executable, bash executes it in a child process, causing builtins like `cd` or `export` to do nothing.

- [How builtins work](https://unix.stackexchange.com/a/266824)
- [zsh use of getcwd()](https://github.com/zsh-users/zsh/blob/00d20ed15e18f5af682f0daec140d6b8383c479a/Src/compat.c#L532)
- [Bash builtins](https://www.gnu.org/software/bash/manual/html_node/Bash-Builtins.html)

[Subject (PDF)](https://cdn.intra.42.fr/pdf/pdf/39166/en.subject.pdf)

# Valgrind

To avoid memory leak of readline being reported by valgrind

```sh
valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell
```

Thanks to [JonathanDUFOUR](https://github.com/JonathanDUFOUR/minishell/blob/cd0dc720ab1d3911afa8831fc81c86415f555e80/ignoreliberror)
