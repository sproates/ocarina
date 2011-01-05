#include <stdio.h>

void print_usage(const char * exe);

int main(int argc, const char ** argv) {
  if(argc < 2) {
    print_usage(argv[0]);
    return 1;
  }
  return 0;
}

void print_usage(const char * exe) {
  printf("Usage: %s <filename>\n", exe);
}
