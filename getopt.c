#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

  int opt;
  while ((opt = getopt(argc, argv, ":bh")) != -1) {
    printf("%c", opt);
  }

  return EXIT_SUCCESS;
}
