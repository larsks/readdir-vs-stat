## Overview

This repository contains two programs that will tell you the "type" (regular file, socket, block/char device, etc) of a given path:

- `get_filetype_readdir` -- use the [`readdir(3)`][readdir] function to determine the file type.
- `get_filetype_stat` -- use the [`stat(2)`][stat] function to determine the file type.

[readdir]: https://man7.org/linux/man-pages/man3/readdir.3.html
[stat]: https://man7.org/linux/man-pages/man2/stat.2.html

They generally result in the same output:

```
$ ./get_filetype_readdir /tmp /run/docker.sock /etc/motd /dev/null
path /tmp type directory
path /run/docker.sock type socket
path /etc/motd type file
path /dev/null type character device
```

```
$ ./get_filetype_stat /tmp /run/docker.sock /etc/motd
path /tmp type directory
path /run/docker.sock type socket
path /etc/motd type file
path /dev/null type character device
```

## Compiling the code 

Run `make` to build the two programs:

```
$ make
cc    -c -o get_filetype_readdir.o get_filetype_readdir.c
cc -o get_filetype_readdir get_filetype_readdir.o
cc    -c -o get_filetype_stat.o get_filetype_stat.c
cc -o get_filetype_stat get_filetype_stat.o
```

## The problem

In the [overview](#overview), the two programs consistently produced the same results. If we run these commands in a rootless Podman container, they produce different output. Using `get_filetype_stat`, we see:

```
$ podman run -it --rm -v $PWD:/code -w /code fedora:latest
[root@d7096e4278a7 code]# ./get_filetype_stat /dev/null
path /dev/null type character device
```

But using `get_filetype_readdir`, we see:

```
$ podman run -it --rm -v $PWD:/code -w /code fedora:latest
[root@052dd40d2fd9 code]# ./get_filetype_readdir /dev/null
path /dev/null type file
```

What's going on?
