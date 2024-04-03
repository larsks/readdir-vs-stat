#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *type_to_name(int dtype) {
  switch (dtype) {
  case DT_BLK:
    return "block device";
  case DT_CHR:
    return "character device";
  case DT_DIR:
    return "directory";
  case DT_FIFO:
    return "fifo";
  case DT_LNK:
    return "link";
  case DT_REG:
    return "file";
  case DT_SOCK:
    return "socket";
  case DT_UNKNOWN:
    return "unknown";
  default:
    return "wtf?";
  }
}

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    char *parent, *name, *path, *pathtmp1, *pathtmp2;
    DIR *dirp;
    struct dirent *entry;

    path = argv[i];
    pathtmp1 = strdup(path);
    pathtmp2 = strdup(path);
    parent = dirname(pathtmp1);
    name = basename(pathtmp2);

    if ((dirp = opendir(parent)) == NULL) {
      perror("opendir");
      exit(1);
    }

    while ((entry = readdir(dirp)) != NULL) {
      if (strcmp(entry->d_name, name) == 0) {
        printf("path %s type %s\n", path, type_to_name(entry->d_type));
      }
    }
  }

  return EXIT_SUCCESS;
}
