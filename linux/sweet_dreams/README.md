# Usage\Test Based Development

What do I want the use of my library to look like?

```c++
#include <pipc/process.hpp>

// executing "ls | grep -E "hello"
pipc::process ls("ls -l"); // initialize with just the name
pipc::process egrep("egrep 'hello'"); // parses command automatically if given a single string

// WAY 1
int pipefd_ls_egrep[2];
if (pipe(pipefd_ls_egrep) < 0) return -1;
ls.redirect_stdout(pipefd_ls_egrep[1]);
egrep.redirect_stdin(pipefd_ls_egrep[0]);
// WAY 2
pipc::conveyor_execute(ls, egrep); // ???
// WAY 3
ls.pipe_2(egrep);
```

## Conveyor: what it can and can't do?

```shell
sweet_dreams$ echo hello | ls # ls does not receive anyhting from echo
README.md  f.txt  hello
sweet_dreams$ ls | echo

sweet_dreams$ ls | grep hello | ls # ls does not receive anything from grep
README.md  f.txt  hello
sweet_dreams$ cat f.txt
hello
sweet_dreams$ cat f.txt | echo

sweet_dreams$
```

Solution? Extra feature: superconveyor? Ability to catch the output?

```c++
// WAY 1
pipc::process ls("ls");
ls.catch_output();
ls.execute();
std::string lsout = ls.output();
/*
// also
int fd = open("file.txt", R_OK);
ls.execute(-1, fd, -1); // forward stdout to fd
// OR
ls.forward_stdout("file.txt");
ls.execute();
*/
// then
pipc::process echo("echo "+lsout);
// OR
std::vector<std::string> args = string_to_args(lsout);
pipc::process echo("echo", args);
```


```c++
pipc::process p(command, args);
p.forward_stdin(filename);
p.forward_stdout(fd);
p.forward_stderr(fd);
p.execute();
// OR
p.execute(filename, fd, fd);
```


