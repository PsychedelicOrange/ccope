#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024

void print_file(const char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror("Error opening file");
    return;
  }

  char buffer[BUFFER_SIZE];
  while (fgets(buffer, BUFFER_SIZE, file)) {
    printf("%s", buffer);
  }
  printf("\n");

  fclose(file);
}

void list_and_print_files(const char *dirpath) {
  DIR *dir = opendir(dirpath);
  if (!dir) {
    perror("Error opening directory");
    return;
  }

  struct dirent *entry;
  char filepath[PATH_MAX];

  while ((entry = readdir(dir))) {
    if (entry->d_type == DT_REG) { // Regular file
      snprintf(filepath, sizeof(filepath), "%s/%s", dirpath, entry->d_name);
      printf("%s", filepath);
    }
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <module_path>\n", argv[0]);
    return EXIT_FAILURE;
  }

  list_and_print_files(argv[1]);
  return EXIT_SUCCESS;
}
