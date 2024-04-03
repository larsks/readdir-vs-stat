#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

char *type_to_name(int mode) {
  switch (mode & S_IFMT) {
  case S_IFSOCK:
    return "socket";
  case S_IFLNK:
    return "link";
  case S_IFREG:
    return "file";
  case S_IFBLK:
    return "block device";
  case S_IFDIR:
    return "directory";
  case S_IFCHR:
    return "character device";
  case S_IFIFO:
    return "fifo";
  default:
    return "unknown";
  }
}

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    char *path;
    struct stat statresult;
    path = argv[i];

    if (stat(path, &statresult) != 0) {
      perror("stat");
      exit(1);
    }

    printf("path %s type %s\n", path, type_to_name(statresult.st_mode));
  }

  return EXIT_SUCCESS;
}
