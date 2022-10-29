## ```execv()```

```c++
execv(args[0], args); // args[0] must be full path to executable
execvp(args[0], args); // looks for args[0] in path
```

### !!! important

The exec() family of functions **replaces** the current process image with a new process image.

that is why it makes sense to ```fork()```

## ```fork()```

```c++
pid_t pid = fork();
if (pid > 0) {
    //we are the parent
    int status;
    waitpid(pid, &status, 0);
} else {
    // we are the child
    execvp(args[0], args); // unlike execv, looks for the program in PATH
}
```

## ```dup2()```

```c++    
int fd = open("file.txt", W_OK)
pid_t pid = fork();
if (pid > 0) {
    //we are the parent
    int status;
    waitpid(pid, &status, 0);
} else {
    // we are the child
   dup2(fd, STDOUT_FILENO); // re-routes output into file.txt
    execvp(args[0], args); // unlike execv, looks for the program in PATH
}

```

## ```pipe()```

try to do ```echo ../src | ls```
information from ```echo``` has to go into ```ls```

```c++
int pipefd[2];
if (pipe(pipefd) < 0)
    return -1;

pid_t pid = fork();
if (pid == 0) {
    dup2(pipefd[1], STDOUT_FILENO);
    execlp("echo", "echo", "../src", NULL);     
} else {
    //we are the parent
    char inbuf[64];
    int nbytes = read(pipefd[0], inbuf, 64);
    std::string data(inbuf, nbytes-1);
    execlp("ls", "ls", data.c_str(), NULL);
    int status;
    waitpid(pid, &status, 0);
 }
```

