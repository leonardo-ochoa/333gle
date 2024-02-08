/*
 * Copyright ©2023 Leonardo Ochoa
 */
// Leonardo Ochoa
// lochoa2
#include <stdio.h>    // for snprintf
#include <stdlib.h>   // for EXIT_SUCCESS, NULL
#include <string.h>   // for strrchr, strcmp, strlen
#include <stdbool.h>  // for bool
#include <dirent.h>   // for directories

#include "ro_file.h"

#define READBUFFERSIZE 128

/*** HELPER FUNCTION DECLARATIONS ******************************************/

// Returns whether or not a filename ends in ".txt".
bool IsTxtFile(char* filename);

// Concatenate the directory and file names into a full path. The caller is
// responsible for freeing the allocated string. Exits if an error occurs.
char* Concatenate(char* dirname, char* filename);

/*
 * This program:
 * - Accepts a directory name as a command-line argument.
 * - Scans through the directory looking for all files whose names end with
 *   the four characters ".txt".
 * - For every such file found, write the contents of those files to stdout
 *   without adding any additional characters or formatting.
 *   Eventually reading the files with ro_file module.
 */
int main(int argc, char** argv) {
  // check arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: ./ex4.c <path>\n");
    return EXIT_FAILURE;
  }
  // open directory
  DIR* dir = opendir(argv[1]);
  if (dir == NULL) {
    fprintf(stderr, "Could not open directory\n");
    return EXIT_FAILURE;
  }
  RO_FILE* file;
  char read_buf[READBUFFERSIZE + 1];
  size_t read_len;
  struct dirent *entry;
  entry = readdir(dir);
  while (entry != NULL) {
    // check for txt files
    if (IsTxtFile(entry->d_name)) {
        char* con = Concatenate(argv[1] , entry->d_name);
        file = ro_open(con);
        if (file == NULL) {
          perror("ro_open failed to open given file");
          return EXIT_FAILURE;
        }
        // read from file
        while ((read_len = ro_read(read_buf, READBUFFERSIZE, file)) > 0) {
          if (read_len == -1) {
            perror("ro_read failed");
            free(con);
            ro_close(file);
            return EXIT_FAILURE;
          }
          // adjust buffer an print to stdout
          read_buf[read_len] = '\0';
          fprintf(stdout, "%s", read_buf);
        }
        free(con);
        ro_close(file);
    }
    entry = readdir(dir);
  }
  closedir(dir);
  return EXIT_SUCCESS;
}

/*** HELPER FUNCTION DEFINITIONS *******************************************/

bool IsTxtFile(char* filename) {
  char* dot = strrchr(filename, '.');
  return dot && !strcmp(dot, ".txt");
}

char* Concatenate(char* dirname, char* filename) {
  bool has_trailing_slash = dirname[strlen(dirname) - 1] == '/';
  // Concatenate directory and file name.
  size_t dlen = strlen(dirname);
  size_t flen = strlen(filename);
  // Malloc space for full path name:
  // dlen + strlen("/") + flen + strlen('\0') = dlen + flen + 2
  int size_to_malloc = has_trailing_slash ? dlen + flen + 1 : dlen + flen + 2;
  char* fullpath = (char*) malloc(sizeof(char) * (size_to_malloc));
  if (fullpath == NULL) {
    fprintf(stderr, "Error on malloc.\n");
    exit(EXIT_FAILURE);
  }
  if (has_trailing_slash) {
    snprintf(fullpath, size_to_malloc, "%s%s", dirname, filename);
  } else {
    snprintf(fullpath, size_to_malloc, "%s/%s", dirname, filename);
  }
  return fullpath;
}
