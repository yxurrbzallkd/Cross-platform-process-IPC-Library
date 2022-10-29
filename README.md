# PIPC project

# Project Description

> Create a cross-platform c++ class library for working with processes and IPC (inter process communication). An analog of boost.processes + boost.interprocess. Requirement: has to support at least 3 OS: Windows, LINUX and one of MacOS/MINIX/FreeBSD, has to contatin **examples**, **tests***, **basic documentation***.

# Project Plan

1. [Installation](#installation)
2. [Theory](#theory)

# Installations

0) Windows 11 - host OS, WSL2 with Ubuntu 20.04 for Linux
1) MINIX - with VirtualBox
2) FreeBSD - ran into a problem - it keeps rebooting after installation...
3) Boost.process and Boost.interprocess - look in experiments-and-demos/boost. Managed to compile a little program with a bunch of imports.

# Theory

This is mostly an educational project, so I intend to illustrate various important theoretical concepts while making it.

1. remember the theory behind **process**:
	1. creation of processes on Linux (```fork``` \ ```exec``` \ ```spawn```)
	2. creation of processes on Windows
	3. structure of a process (! on different OS's)
2. remember the theory behind [**IPC**](#how-to-ipc):
	1. pipes
	2. shared memory
	3. mmap-files
	4. sockets
	5. locks
	6. mutexes
	7. etc.
3. research the [differences](#ipc-approaches) of processes and IPC in different OS's
4. learn by [example](#how-others-did-it):
	1. ```Boost.processes + Boost.Interprocess```
	2. Python ```multiprocess```


### Creating processes

[see this for Windows and Linux process creation](./experiments-and-demos/pipes/README.md)

## How to IPC

### Python examples

[Python multiprocessing](https://docs.python.org/3/library/multiprocessing.html)

Will be filled soon...

### Boost examples

[Boost.process+Boost.Interprocess](https://www.boost.org/)

[Boost examples directory](./experiments-and-demos/boost)

# Unix vs WINDOWS

[see this file. it is not much, but all i have so far](./experiments-and-demos/pipes/README.md)

# Unix vs Windows vs MINIX? vs ?FreeBSD

later

### Playing with processes from command line

```/proc``` - pseudo file system (?). a directory of Linux that contains information on all running processes

[More Here](https://www.kernel.org/doc/Documentation/filesystems/proc.txt) and [the linux documentation](https://man7.org/linux/man-pages/man5/proc.5.html)

```console
diana@LAPTOP-3EIHGG93:/mnt/Users/Diana/project$ ps # list processes
  PID TTY          TIME CMD
 1515 pts/1    00:00:01 bash
 1539 pts/1    00:00:00 ps
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ pstree
init─┬─init───init───bash
     ├─init───init───bash───pstree
     └─2*[{init}]
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ps -aux # list all processes from all users
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.0   1756  1088 ?        Sl   Oct26   0:00 /init
root         7  0.0  0.0   1764    76 ?        Ss   Oct26   0:00 /init
root         8  0.0  0.0   1764    92 ?        S    Oct26   0:03 /init
diana        9  0.0  0.1  10192  5096 pts/0    Ss+  Oct26   0:00 -bash
root      1513  0.0  0.0   1768    88 ?        Ss   17:07   0:00 /init
root      1514  0.0  0.0   1768   100 ?        R    17:07   0:01 /init
diana     1515  0.0  0.1  10192  5128 pts/1    Ss   17:07   0:01 -bash
diana     1668  0.0  0.0  10856  3356 pts/1    R+   17:39   0:00 ps -aux
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls /proc
1     8          cmdline    diskstats    interrupts  key-users    loadavg  mounts        schedstat  sysvipc      vmallocinfo
1513  9          config.gz  dma          iomem       keys         locks    mtrr          self       thread-self  vmstat
1514  acpi       consoles   driver       ioports     kmsg         mdstat   net           softirqs   timer_list   zoneinfo
1515  buddyinfo  cpuinfo    execdomains  irq         kpagecgroup  meminfo  pagetypeinfo  stat       tty
1540  bus        crypto     filesystems  kallsyms    kpagecount   misc     partitions    swaps      uptime
7     cgroups    devices    fs           kcore       kpageflags   modules  sched_debug   sys        version
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls /proc/1515
arch_status  cgroup      comm             cwd      fd       io         maps       mounts      ns         oom_score_adj  projid_map  schedstat  smaps_rollup  statm    task           uid_map
attr         clear_refs  coredump_filter  environ  fdinfo   limits     mem        mountstats  oom_adj    pagemap        root        setgroups  stack         status   timers         wchan
auxv         cmdline     cpuset           exe      gid_map  map_files  mountinfo  net         oom_score  personality    sched       smaps      stat          syscall  timerslack_ns
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls /proc/1515/cwd # == to ls
freeBSD  minix  theory
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls -ls /proc/1515/ | grep "\->" # so, cwd is actually a symlink - interesting... let's check
0 lrwxrwxrwx  1 diana diana 0 Oct 27 17:09 cwd -> /mnt/c/Users/Diana/project
0 lrwxrwxrwx  1 diana diana 0 Oct 27 17:09 exe -> /usr/bin/bash
0 lrwxrwxrwx  1 diana diana 0 Oct 27 17:09 root -> /
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls /proc/self/task # pid of the currently executed process (that is - ls)
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ cat /proc/1515/stack
cat: /proc/1515/stack: Permission denied
```

```console
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls /proc/1515/map_files # lists some files. notice - those are all symlinks! where are they pointing to?
```
[ls /proc/115/map_files](./theory/ls.proc.115.map_files.txt)

```console
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls -la /proc/1515/map_files
```
[ls -la proc/115/map_files](./theory/ls.-la.proc.1515.map_files.txt)

```console
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ cat  /proc/1515/maps
```
[cat proc/115/maps](./theory/cat.proc.1515.maps.txt)

```console
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ cat /proc/1515/io
rchar: 10609401
wchar: 34473
syscr: 4154
syscw: 672
read_bytes: 0
write_bytes: 0
cancelled_write_bytes: 0
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ cat /proc/1515/io # the rchar, wchar, syscr, syscw will change, because we have typed in a new command
rchar: 10616799
wchar: 34778
syscr: 4175
syscw: 676
read_bytes: 0
write_bytes: 0
cancelled_write_bytes: 0
```

```console
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ cat /proc/1515/pagemap > file.txt # won't work - it is a virtual file with 2^25 64 bit wide entries for pages - ATTENTION! this is exactly what is used to translate from virtual to physical addresses
^C^C^C^C
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ stat file.txt
  File: file.txt
  Size: 20303446016  Blocks: 39655168   IO Block: 4096   regular file
Device: 40h/64d Inode: 58265320179233666  Links: 1
Access: (0777/-rwxrwxrwx)  Uid: ( 1000/   diana)   Gid: ( 1000/   diana)
Access: 2022-10-27 17:19:16.559209500 +0300
Modify: 2022-10-27 17:19:09.960279300 +0300
Change: 2022-10-27 17:19:09.960279300 +0300
 Birth: -
```

```console
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ cat  /proc/self/status | head -n 7
Name: cat
Umask:  0022
State:  R (running)
Tgid: 1621
Ngid: 0
Pid: 1621
PPid: 1515
```

```console
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ cat /proc/interrupts
```
[cat /proc/interrupts](./theory/cat.proc.interrupts.txt)
``` 
diana@LAPTOP-3EIHGG93:/mnt/c/Users/Diana/project$ ls /proc/irq
0  1  10  11  12  13  14  15  2  24  25  26  27  28  29  3  30  31  32  4  5  6  7  8  9  default_smp_affinity
```

### Playing with processes in ```bash```

use ```fork``` (~```&``` in ```bash```) to create a new process, print a process tree

```bash
#!/usr/bin/bash
ps
sleep 5 & # fork a new process
pstree
```
```shell
$ bash -x process_demo.sh
+ ps
  PID TTY          TIME CMD
 1515 pts/1    00:00:01 bash
 1731 pts/1    00:00:00 bash
 1732 pts/1    00:00:00 ps
+ sleep 5
+ pstree
init─┬─init───init───bash
     ├─init───init───bash───bash─┬─pstree
     │                           └─sleep
     └─2*[{init}]
```
